#include "parser.hpp"

std::unique_ptr<statement::statement_base> parser::parse_statement(const bool is_function_parameter) {
	// get our current lexeme and its information so we don't need to call these functions every time we need to reference it
	lexeme current_lex = this->current_token();

	// create a shared_ptr to the statement we are going to parse so that we can return it when we are done
	std::unique_ptr<statement::statement_base> stmt = nullptr;

	// first, we will check to see if we need any keyword parsing
	if (current_lex.type == enumerations::lexeme_type::KEYWORD_LEX) {

		// Check to see what the keyword is

		// parse an "include" directive
		if (current_lex.value == "include") {
			stmt = this->parse_include(current_lex);
		}
		// parse a declaration
		else if (current_lex.value == "decl") {
			stmt = this->parse_declaration(current_lex, is_function_parameter);
		}
		// parse an ITE
		else if (current_lex.value == "if") {
			stmt = this->parse_ite(current_lex);
		}
		// pare an allocation
		else if (current_lex.value == "alloc") {
			stmt = this->parse_allocation(current_lex, is_function_parameter);
		}
		// Parse an assignment
		else if (current_lex.value == "let") {
			stmt = this->parse_assignment(current_lex);
		}
		else if (current_lex.value == "move") {
			stmt = this->parse_move(current_lex);
		}
		// Parse a return statement
		else if (current_lex.value == "return") {
			stmt = this->parse_return(current_lex);
		}
		// Parse a 'while' loop
		else if (current_lex.value == "while") {
			stmt = this->parse_while(current_lex);
		}
		// Parse a definition -- could be function or struct, call the delegator
		else if (current_lex.value == "def") {
			stmt = this->parse_definition(current_lex);
		}
		else if (current_lex.value == "pass") {
			this->next();
		}
		else if (current_lex.value == "construct")
		{
			stmt = this->parse_construction();
			stmt->set_line_number(current_lex.line_number);
		}
		else {
			throw error::compiler_exception("Invalid keyword", 211, current_lex.line_number);
		}

	}
	// if it's not a keyword, check to see if we need to parse a function call
	else if (current_lex.type == enumerations::lexeme_type::OPERATOR)
	{
		if (current_lex.value == "@") {
			stmt = this->parse_function_call(current_lex);
		}
		else {
			throw error::compiler_exception(
                "Lexeme '" + current_lex.value + "' is not a valid beginning to a statement",
                000,
                current_lex.line_number
            );
		}
	}
	// otherwise, we might have a scoped block statement
	else if (current_lex.value == "{") {
		// eat the curly brace
		this->next();
		statement::statement_block scope_ast = this->create_ast();
		this->next();	// eat the closing curly brace
		// NB: scope blocks never need semicolons

		// create the statement
		stmt = std::make_unique<statement::scoped_block>(scope_ast);
	}

	// if it is a curly brace, advance the character and return a nullptr; the compiler will skip this
	else if (current_lex.value == "}") {
		this->next();
	}

	// otherwise, if the lexeme is not a valid beginning to a statement, abort
	else {
		throw error::compiler_exception("Lexeme '" + current_lex.value + "' is not a valid beginning to a statement", 000, current_lex.line_number);
	}

	return stmt;
}

std::unique_ptr<statement::statement_base> parser::parse_include(lexeme current_lex)
{
	lexeme next = this->next();

	if (next.type == enumerations::lexeme_type::STRING_LEX) {
		std::string filename = next.value;

		auto stmt = std::make_unique<statement::include>(filename);
		stmt->set_line_number(current_lex.line_number);
		
		return stmt;
	}
	else {
		throw error::compiler_exception("Expected a filename in quotes in 'include' statement", 0, current_lex.line_number);
		// TODO: error numbers for includes
	}
}

std::unique_ptr<statement::statement_base> parser::parse_declaration(lexeme current_lex, bool is_function_parameter) {
	/*

	Parse a declaration statement. Appropriate syntax is:
		decl <type> <name>;
	or
		decl <type> <name>(<formal parameters>);
	where the formal parameters are also declarations, or
		decl struct <name>;

	*/

	lexeme next_lexeme = this->next();
	std::unique_ptr<expression::expression_base> initial_value = nullptr;
	std::unique_ptr<statement::declaration> stmt = nullptr;

	// the next lexeme must be a keyword (specifically, a type or 'struct')
	if (next_lexeme.value == "struct") {
		// struct declaration
		if (this->peek().type == enumerations::lexeme_type::IDENTIFIER_LEX) {
			data_type struct_type(
				enumerations::primitive_type::STRUCT,
				enumerations::primitive_type::NONE,
				symbol_qualities(),
				nullptr,
				this->next().value
			);
			stmt = std::make_unique<statement::declaration>(struct_type, "", std::move(initial_value), false, true);
		}
		else {
			throw error::compiler_exception("Expected struct name", error_code::ILLEGAL_STRUCT_NAME, this->current_token().line_number);
		}
	}
	else if (next_lexeme.type == enumerations::lexeme_type::KEYWORD_LEX) {
		data_type symbol_type_data = this->get_type();
		
		// get the variable name
		next_lexeme = this->next();
		if (next_lexeme.type == enumerations::lexeme_type::IDENTIFIER_LEX) {		// variable names must be identifiers; if an identifier doesn't follow the type, we have an error
			// get our variable name
			std::string var_name = next_lexeme.value;
			bool is_function = false;

			// check to see if we have postfixed symbol qualities
			if (this->peek().value == "&") {
				// append the posftixed qualities to symbol_type_data.qualities
				this->next();
				symbol_qualities postfixed_qualities = this->get_postfix_qualities(is_function_parameter ? "(" : "");
				try {
					symbol_type_data.add_qualities(postfixed_qualities);
				} catch(std::string &offending_quality) {
					throw error::quality_conflict(offending_quality, this->current_token().line_number);
				}
			}

			std::vector<std::unique_ptr<statement::statement_base>> formal_parameters = {};

			// next, check to see if we have a paren following the name; if so, it's a function, so we need to get the formal parameters
			if (this->peek().value == "(") {
				// if there is a paren, it's a function declaration
				is_function = true;

				// todo: parse function declarations
				this->next();	// eat the opening paren

				// so long as we haven't hit the end of the formal parameters, continue parsing
				while (this->peek().value != ")") {
					this->next();
					std::unique_ptr<statement::statement_base> next = this->parse_statement(true);

					// the statement _must_ be a declaration, not an allocation
					if (next->get_statement_type() == enumerations::statement_type::DECLARATION) {
						formal_parameters.push_back(std::move(next));
					}
					else {
						throw error::compiler_exception("Definitions of formal parameters in a declaration of a function must use 'decl' (not 'alloc'", 0,
							this->current_token().line_number);
					}

					if (this->peek().value == ",") {
						this->next();
					}
				}

				this->next();	// eat the closing paren
			}
			// otherwise, if the name is followed by a colon, we have a default value
			else if (this->peek().value == ":") {
				// however, we may only use alloc-assign syntax if the 'decl' is part of a function parameter
				if (is_function_parameter) {
					this->next();
					this->next();	// parse_expression(...) begins on the _first token_ of the expression
					initial_value = this->parse_expression();
				}
				else {
					throw error::compiler_exception("Cannot use alloc-assign syntax in declarations unless said declaration is a default function parameter",
						this->current_token().line_number);
				}
			}
			
			// finally, we must have a semicolon, a comma, or a closing paren
			if (this->peek().value == ";" || this->peek().value == "," || this->peek().value == ")") {
				stmt = std::make_unique<statement::declaration>(symbol_type_data, var_name, std::move(initial_value), is_function, false, formal_parameters);
				stmt->set_line_number(next_lexeme.line_number);
			}
			else if (this->peek().value == ":") {
				throw error::compiler_exception("Initializations are forbidden in declaration statements", 0, next_lexeme.line_number);
			}
			else {
				throw error::expected_semicolon(next_lexeme.line_number);
			}
		}
		else {
			throw error::compiler_exception("Expected variable name after type in declaration", 0, next_lexeme.line_number);
		}
	}
	// if it is not followed by a type name, throw an exception
	else {
		throw error::compiler_exception("Expected type name following 'decl' in variable declaration", 0, current_lex.line_number);
	}

	return stmt;
}

std::unique_ptr<statement::statement_base> parser::parse_ite(lexeme current_lex)
{
	// Get the next lexeme
	lexeme next = this->next();

	// Check to see if condition is enclosed in parens
	if (next.value == "(") {
		// create the statement pointer
		std::unique_ptr<statement::statement_base> stmt = nullptr;

		// get the condition
		this->next();
		std::unique_ptr<expression::expression_base> condition = this->parse_expression();

		if (this->peek().value == ")")
			this->next();
		else
			throw error::compiler_exception("Expected ')' in conditional", error_code::MISSING_GROUPING_SYMBOL_ERROR, this->current_token().line_number);
		
		// Initialize the if_block
		std::unique_ptr<statement::statement_base> if_branch = nullptr;
		std::unique_ptr<statement::statement_base> else_branch = nullptr;
		
		// create the branch
		this->next();	// skip ahead to the first character of the statement
		if_branch = this->parse_statement();

		// if there was a single statement, ensure there was a semicolon
		if (this->peek().value == ";")
			this->next();
		else {
			if (this->current_token().value != "}")
				throw error::expected_semicolon(this->current_token().line_number);
		}

		// Check for an else clause
		if (!this->is_at_end() && this->peek().value == "else") {
			// if we have an else clause
			this->next();	// skip the keyword
			this->next();	// skip ahead to the first token in the statment

			// parse the statement
			else_branch = this->parse_statement();

			// construct the statement and return it
			stmt = std::make_unique<statement::if_else>(std::move(condition), std::move(if_branch), std::move(else_branch));
		}
		else {
			// if we do not have an else clause, we will return the if clause alone here
			stmt = std::make_unique<statement::if_else>(std::move(condition), std::move(if_branch));
		}

		stmt->set_line_number(current_lex.line_number);
		return stmt;
	}
	// If condition is not enclosed in parens
	else {
		throw error::compiler_exception("Condition must be enclosed in parens", 331, current_lex.line_number);
	}
}

std::unique_ptr<statement::statement_base> parser::parse_allocation(lexeme current_lex, bool is_function_parameter)
{
	// check our next token; it must be a keyword or a struct name (ident)
	lexeme next_token = this->next();
	if (next_token.type == enumerations::lexeme_type::KEYWORD_LEX || next_token.type == enumerations::lexeme_type::IDENTIFIER_LEX) {
		// get the type data using parser::get_type() -- this will tell us if the memory is to be dynamically allocated
		// It will also throw an exception if the type specifier was invalid
		data_type symbol_type_data = this->get_type();

		// next, get the name
		if (this->peek().type == enumerations::lexeme_type::IDENTIFIER_LEX) {
			next_token = this->next();
			std::string new_var_name = next_token.value;

			// get our postfixed qualities, if we have any
			// now, get postfixed symbol qualities, if we have any
			if (this->peek().value == "&") {
				// append the posftixed qualities to symbol_type_data.qualities
				this->next();
				symbol_qualities postfixed_qualities = this->get_postfix_qualities(is_function_parameter ? "(" : "");

				// we may encounter an error when trying to add our postfixed qualities; catch it and craft a new exception that includes the line number
				try {
					symbol_type_data.add_qualities(postfixed_qualities);
				} catch (std::string &offending_quality) {
					throw error::quality_conflict(offending_quality, this->current_token().line_number);
				}
			}

			// ensure the type is valid before proceeding
			if (data_type::is_valid_type(symbol_type_data))
			{

				bool initialized = false;
				std::unique_ptr<expression::expression_base> initial_value = nullptr;

				// the name can be followed by a semicolon, a comma, a closing paren, or a colon
				// if it's a colon, we have an initial value
				if (this->peek().value == ":") {
					this->next();
					this->next();	// advance the iterator so it points to the first character of the expression
					initialized = true;
					initial_value = this->parse_expression();
				}

				// if it's a semicolon, comma, or closing paren, craft the statement and return
				if (this->peek().value == ";" || this->peek().value == "," || this->peek().value == ")") {
					// craft the statement
					auto stmt = std::make_unique<statement::allocation>(symbol_type_data, new_var_name, initialized, std::move(initial_value));
					stmt->set_line_number(next_token.line_number);	// set the line number
					return stmt;
				}
				// otherwise, it's an invalid character
				else {
					throw error::expected_semicolon(this->current_token().line_number);
				}
			}
			else
			{
				throw error::invalid_type(this->current_token().line_number);
			}
		}
		else {
			throw error::compiler_exception(
                "The variable's type must be followed by a valid identifier",
                error_code::MISSING_IDENTIFIER_ERROR,
                next_token.line_number
            );
		}
	} else {
		throw error::compiler_exception("Expected a valid data type", error_code::TYPE_ERROR, current_lex.line_number);
	}
}

std::unique_ptr<statement::statement_base> parser::parse_assignment(lexeme current_lex)
{
	// parse an expression for our lvalue (the compiler will verify the type later)
	this->next();	// parser::parse_expression must have the token pointer on the first token of the expression
	std::unique_ptr<expression::expression_base> lvalue = this->parse_expression(0, "(", false, true);

	// now, "lvalue" should hold the proper variable reference for the assignment
	// get the operator character, make sure it's an equals sign
	lexeme op_lex = this->next();
	enumerations::exp_operator op = translate_operator(op_lex.value);

	if (is_valid_copy_assignment_operator(op)) {
		// if the next lexeme is not a semicolon and the next lexeme's line number is the same as the current lexeme's line number, we are ok
		if ((this->peek().value != ";") && (this->peek().line_number == current_lex.line_number)) {
			// get our rvalue expression
			this->next();
			std::unique_ptr<expression::expression_base> rvalue = this->parse_expression();

			if (op == enumerations::exp_operator::EQUAL) {
				auto assign = std::make_unique<statement::assignment>(std::move(lvalue), std::move(rvalue));
				assign->set_line_number(current_lex.line_number);
				return assign;
			}
			else
			{
				auto assign = std::make_unique<statement::compound_assignment>(
					std::move(lvalue),
					std::move(rvalue),
					parser::get_compound_arithmetic_op(op)
				);
				assign->set_line_number(current_lex.line_number);
				return assign;
			}
		}
		// otherwise, we have a syntax error -- we didn't get an expression where we expected it
		else {
			throw error::compiler_exception("Expected expression", 0, current_lex.line_number);
		}
	}
	else if (is_valid_move_assignment_operator(op)) {
		throw error::compiler_exception("Move assignment operator not supported with 'let'", error_code::OPERATOR_TYPE_ERROR, op_lex.line_number);
	}
	else {
		throw error::compiler_exception("Unrecognized token.", 0, current_lex.line_number);
	}
}

std::unique_ptr<statement::statement_base> parser::parse_move(lexeme current_lex)
{
	// get the lhs of the movement
	this->next();
	auto lhs = this->parse_expression();
	
	// get the op
	auto op = this->read_operator(false);
	if (is_valid_move_assignment_operator(op)) {
		// get the rhs
		this->next();
		auto rhs = this->parse_expression();

		if (this->peek().value != ";") {
			throw error::expected_semicolon(this->current_token().line_number);
		}

		// todo: ensure that we are only moving modifiable-lvalues (should this be done in the compiler class?)
		// todo: do this in a semantic analysis phase
		
		std::unique_ptr<statement::statement_base> stmt = nullptr;
		if (op == enumerations::exp_operator::LEFT_ARROW) {
			// rhs is rvalue (the value)
			stmt = std::make_unique<statement::movement>(std::move(lhs), std::move(rhs));
		}
		else {
			// lhs is rvalue (the value)
			stmt = std::make_unique<statement::movement>(std::move(rhs), std::move(lhs));
		}

        stmt->set_line_number(current_lex.line_number);
		return stmt;
	}
	else {
		throw error::compiler_exception("Expected move assignment operator", error_code::OPERATOR_TYPE_ERROR, current_lex.line_number);
	}
}

std::unique_ptr<statement::statement_base> parser::parse_return(lexeme current_lex)
{
	std::unique_ptr<statement::statement_base> stmt = nullptr;
	this->next();	// go to the expression

	// if the current token is a semicolon, return a expression::literal Void
	if (this->current_token().value == ";" || this->current_token().value == "void") {
		// if we have "void", we need to skip ahead to the semicolon
		if (this->current_token().value == "void") {
			if (this->peek().value == ";") {
				this->next();
			}
			else {
				// we expect a semicolon after the return statement; throw an exception if there isn't one
				throw error::expected_semicolon(current_lex.line_number);
			}
		}

		// craft the statement
		stmt = std::make_unique<statement::return_statement>(
			std::make_unique<expression::literal>(enumerations::primitive_type::VOID, "", enumerations::primitive_type::NONE)
		);
		stmt->set_line_number(current_lex.line_number);
	}
	// otherwise, we must have an expression
	else {
		// get the return expression
		auto return_exp = this->parse_expression();

		// create a return statement from it and set the line number
		stmt = std::make_unique<statement::return_statement>(std::move(return_exp));
		stmt->set_line_number(current_lex.line_number);
	}

	// return the statement
	return stmt;
}

std::unique_ptr<statement::statement_base> parser::parse_while(lexeme current_lex)
{
	// A while loop is very similar to an ITE in how we parse it; the only difference is we don't need to check for an "else" branch
	lexeme next = this->next();

	if (next.value == "(") {
		// get condition
		this->next();
		auto condition = this->parse_expression();
		
		if (this->peek().value == ")")
		{
			this->next();
		}
		else
		{
			throw error::compiler_exception("Expected parentheses around conditional", error_code::MISSING_GROUPING_SYMBOL_ERROR, this->current_token().line_number);
		}

		// create the branch
		this->next();
		auto branch = this->parse_statement();

		// if there was a single statement, ensure there was a semicolon
		if (this->peek().value == ";")
			this->next();
		else if (this->current_token().value != "}")
			throw error::expected_semicolon(this->current_token().line_number);
		
		auto stmt = std::make_unique<statement::while_loop>(std::move(condition), std::move(branch));
		stmt->set_line_number(current_lex.line_number);
		return stmt;
	}
	else {
		throw error::compiler_exception("Expected a condition", 331, current_lex.line_number);
	}
}

std::unique_ptr<statement::statement_base> parser::parse_function_call(lexeme current_lex)
{
    auto parsed = this->parse_expression();
    if (parsed->get_expression_type() == enumerations::expression_type::CALL_EXP) {
        expression::call *exp = static_cast<expression::call*>(parsed.get());

        // if we didn't get a call expression, then it's an error -- we /must/ have one for a Call statement 
        // this means if we have a binary or something else (e.g., '@x.y().z'), it's not valid
        auto stmt = std::make_unique<statement::call>(*exp);
        stmt->set_line_number(current_lex.line_number);
		return stmt;
    }
    else {
        throw error::compiler_exception(
            "Expected a valid function call expression",
            error_code::INVALID_EXPRESSION_TYPE_ERROR,
            current_lex.line_number
        );
    }
}
