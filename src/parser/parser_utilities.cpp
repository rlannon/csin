#include "parser.hpp"

using ops = enumerations::exp_operator;

const std::unordered_map<ops, size_t> parser::op_precedence({
	{ops::RIGHT_ARROW, 1},
	{ops::LEFT_ARROW, 1},
	{ops::PLUS_EQUAL, 1},
	{ops::MINUS_EQUAL, 1},
	{ops::MULT_EQUAL, 1},
	{ops::DIV_EQUAL, 1},
	{ops::MOD_EQUAL, 1},
	{ops::AND_EQUAL, 1},
	{ops::OR_EQUAL, 1},
	{ops::XOR_EQUAL, 1},
	{ops::OR, 2},
	{ops::AND, 2},
	{ops::XOR, 2},
	{ops::BIT_AND, 3},
	{ops::BIT_OR, 3},
	{ops::BIT_XOR, 3},
	{ops::LESS, 7},
	{ops::GREATER, 7},
	{ops::LESS_OR_EQUAL, 7},
	{ops::GREATER_OR_EQUAL, 7},
	{ops::EQUAL, 7},
	{ops::NOT_EQUAL, 7},
	{ops::LEFT_SHIFT, 8},
	{ops::RIGHT_SHIFT, 8},
	{ops::PLUS, 10},
	{ops::MINUS, 10},
	{ops::MULT, 15},
	{ops::DIV, 15},
	{ops::MODULO, 15},
	{ops::TYPECAST, 20},
	{ops::NOT, 20},
	{ops::BIT_NOT, 20},
	{ops::UNARY_PLUS, 20},
	{ops::UNARY_MINUS, 20},
	{ops::ADDRESS, 20},
	{ops::DEREFERENCE, 20},
	{ops::ATTRIBUTE_SELECTION, 23},
	{ops::CONTROL_TRANSFER, 24},
	{ops::PROC_OPERATOR, 25},
    {ops::DOT, 25},
	{ops::INDEX, 25},
	{ops::SCOPE_RESOLUTION, 30}
});

enumerations::exp_operator parser::read_operator(bool peek) {
	// reads an operator from the lex stream
	ops op;
	lexeme l = this->next();
	if (is_valid_operator(this->peek())) {
		op = translate_operator(l.value + this->next().value);
		if (op == ops::NO_OP) {
			this->back();
			op = translate_operator(l.value);
		}
		else if (peek) {
			this->back();
		}
	}
	else {
		op = translate_operator(l.value);
	}

	if (peek)
		this->back();

	return op;
}

bool parser::is_valid_operator(lexeme l) {
    return lexer::is_valid_operator(l.value);
}

enumerations::exp_operator parser::translate_operator(const std::string& op_string) {
	// try and find the operator
	auto it = lexer::op_strings.find(op_string);
	if (it == lexer::op_strings.end()) {
		return enumerations::exp_operator::NO_OP;
	}
	else {
		return it->second;
	}
}

bool parser::is_valid_copy_assignment_operator(enumerations::exp_operator op) {
	using ops = enumerations::exp_operator;
	return (
		op == ops::EQUAL ||
		op == ops::PLUS_EQUAL ||
		op == ops::MINUS_EQUAL ||
		op == ops::MULT_EQUAL ||
		op == ops::DIV_EQUAL ||
		op == ops::MOD_EQUAL ||
		op == ops::AND_EQUAL ||
		op == ops::OR_EQUAL ||
		op == ops::XOR_EQUAL ||
		op == ops::LEFT_SHIFT_EQUAL ||
		op == ops::RIGHT_SHIFT_EQUAL
	);
}

bool parser::is_valid_move_assignment_operator(enumerations::exp_operator op) {
	return (op == enumerations::exp_operator::LEFT_ARROW || op == enumerations::exp_operator::RIGHT_ARROW);
}

size_t parser::get_precedence(const std::string& symbol, size_t line) {
	// get the precedence of an operator based on the string

	size_t precedence = 0;
	return parser::get_precedence(parser::translate_operator(symbol), line);
}

size_t parser::get_precedence(enumerations::exp_operator op, size_t line) {
	size_t precedence = 0;
	
	std::unordered_map<enumerations::exp_operator, size_t>::const_iterator it = parser::op_precedence.find(op);
	if (it == parser::op_precedence.end()) {
		throw error::compiler_exception("Invalid operator", 0, line);
	}
	else {
		precedence = it->second;
	}

	return precedence;
}

// Utility functions for traversing the token list

bool parser::is_at_end() {
	if (this->position >= this->num_tokens - 2 || this->num_tokens == 0) {
		return true;
	}
	else {
		return false;
	}
}

lexeme parser::peek() {
	if (position + 1 < this->tokens.size()) {
		return this->tokens[this->position + 1];
	}
	else {
		throw error::compiler_exception("No more lexemes to parse!", 1, this->tokens[this->position].line_number);
	}
}

lexeme parser::next() {
	// Increments the position and returns the token there, provided we haven't hit the end

	// increment the position
	this->position += 1;

	// if we haven't hit the end, return the next token
	if (position < this->tokens.size()) {
		return this->tokens[this->position];
	}
	// if we have hit the end
	else {
		throw error::compiler_exception("No more lexemes to parse!", 1, this->tokens[this->position - 1].line_number);
	}
}

lexeme parser::current_token() {
	return this->tokens[this->position];
}

lexeme parser::previous() {
	return this->tokens[this->position - 1];
}

lexeme parser::back() {
	this->position -= 1;
	return this->tokens[this->position];
}

void parser::skipPunc(char punc) {
	if (this->current_token().type == enumerations::lexeme_type::PUNCTUATION) {
		if (this->current_token().value[0] == punc) {
			this->position += 1;
			return;
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}

bool parser::is_type(const std::string& lex_value)
{
	std::vector<std::string> types = {
		"int",
		"bool",
		"string",
		"char",
		"float",
		"raw",
		"ptr",
		"array",
		"struct",
		"tuple",
		"void"
	};

	// iterate through our list of type names
	size_t i = 0;
	bool found = false;
	auto it = types.begin();
	while (it != types.end() && !found) {
		if (lex_value == *it) {
			found = true;
		}
		else {
			it++;
		}
	}

	return found;
}

std::string parser::get_closing_grouping_symbol(const std::string& beginning_symbol)
{
	/*

	Returns the appropriate closing symbol for some opening grouping symbol 'beginning_symbol'; e.g., if beginning_symbol is '(', the function will return ')'

	Operates with strings because that's what lexemes use

	*/

	if (beginning_symbol == "(") {
		return ")";
	}
	else if (beginning_symbol == "[") {
		return "]";
	}
	else if (beginning_symbol == "{") {		// while curly braces are not considered grouping symbols by these functions, we will include it here
		return "}";
	}
	else if (beginning_symbol == "<") {
		return ">";
	}
	else {
		throw error::compiler_exception("Invalid grouping symbol in expression", error_code::INVALID_TOKEN, 0);
		return "";
	}
}

bool parser::is_opening_grouping_symbol(const std::string& to_test)
{
	/*

	Checks to see whether a given string is a opening parenthesis or a bracket.
	Curly braces not included here because they are not considered grouping symbols like ( and [ -- they serve a different purpose

	*/
	return (to_test == "(" || to_test == "[" || to_test == "{");
}

bool parser::has_return(const statement::statement_block& to_test)
{
	// our base case is that the statement block has a return statement
	if (to_test.has_return)
	{
		return true;
	}
	// if it doesn't, check to see whether we have a scope block in the last statement
	else {
		// if we have no statements in the scope block, we obviously have no return statement
		if (to_test.statements_list.size() == 0)
		{
			return false;
		}
		else
		{
			statement::statement_base* last_statement = to_test.statements_list.back().get();
			if (last_statement->get_statement_type() == enumerations::statement_type::IF_THEN_ELSE)
			{
				statement::if_else* ite = static_cast<statement::if_else*>(last_statement);

				bool returns = general_utilities::ite_returns(ite);

				// if both branches return a value, we are golden
				if (!returns) {
					throw error::no_return(last_statement->get_line_number());
				}
				
				return returns;
			}
			else if (last_statement->get_statement_type() == enumerations::statement_type::WHILE_LOOP)
			{
				statement::while_loop* while_loop = static_cast<statement::while_loop*>(last_statement);

				// while loops are a little simpler, we can simply pass in the branch for the while loop
				const statement::statement_base* branch = while_loop->get_branch();
				if (branch)
				{
					return general_utilities::returns(*branch);
				}
				else
				{
					return false;
				}
    		}
			else
			{
				return false;
			}
		}
	}
}

data_type parser::get_type(const std::string& grouping_symbol)
{
	// check our qualities, if any
	symbol_qualities qualities = this->get_prefix_qualities(grouping_symbol);

	// todo: should we set the 'dynamic' quality if we have a string?

	// get the current lexeme
	lexeme current_lex = this->current_token();

	enumerations::primitive_type new_var_type;
	data_type new_var_subtype;
	std::shared_ptr<expression::expression_base> array_length_exp = nullptr;
	std::string struct_name = "";
	bool subtype_is_list = false;
	std::vector<data_type> subtypes;

	if (current_lex.value == "ptr" || current_lex.value == "ref") {
		// set the type
		new_var_type = current_lex.value == "ptr" ? enumerations::primitive_type::PTR : enumerations::primitive_type::REFERENCE;

		// 'ptr' must be followed by '<'
		if (this->peek().value == "<") {
			this->next();
			
			new_var_subtype = this->parse_subtype("<");
		}
		// if it's not, we have a syntax error
		else {
			throw error::compiler_exception(
				"Proper syntax is 'alloc ptr< T >' or 'alloc ref< T >'",
				error_code::INVALID_TYPE_SYNTAX,
				current_lex.line_number
			);
		}
	}
	// otherwise, if it's an array,
	else if (current_lex.value == "array") {
		new_var_type = enumerations::primitive_type::ARRAY;
		// check to make sure we have the size and type in angle brackets
		if (this->peek().value == "<") {
			this->next();	// eat the angle bracket

			// if the next value is a keyword, we can leave array_length_exp as a nullptr
			if (this->peek().type == enumerations::lexeme_type::KEYWORD_LEX) {
				new_var_subtype = this->parse_subtype("<");
			} else {
				// parse an expression to obtain the array length; the _current lexeme_ should be the first lexeme of the expression		
				this->next();
				array_length_exp = this->parse_expression();
				
				// the array length will be evaluated by the compiler; continue parsing

				// a comma should follow the size
				if (this->peek().value == ",") {
					this->next();
						
					// parse a full type
					new_var_subtype = this->parse_subtype("<");
				}
				else {
					throw error::compiler_exception(
						"The size of an array must be followed by the type",
						error_code::INVALID_TYPE_SYNTAX,
						current_lex.line_number
					);
				}
			}
		}
		else {
			throw error::compiler_exception(
				"Proper syntax is 'array< N, T >' where N an integer expression and T is the contained type",
				error_code::INVALID_TYPE_SYNTAX,
				current_lex.line_number
			);
		}
	}
	else if (current_lex.value == "tuple") {
		// tuples contain an arbitrarily long list of types separated by commas
		new_var_type = enumerations::primitive_type::TUPLE;
		subtype_is_list = true;
		if (this->peek().value == "<") {
			this->next();
			while (this->peek().type == enumerations::lexeme_type::KEYWORD_LEX) {
				// get the type
				this->next();
				data_type sub = this->get_type();
				subtypes.push_back(sub);

				// check to see what needs to happen next
				if (this->peek().value == ",") {
					this->next();
				}
				else if (this->peek().value != ">") {
					throw error::compiler_exception(
						"Expected type, comma, or closing angle bracket",
						error_code::INVALID_TYPE_SYNTAX,
						this->current_token().line_number
					);
				}
			}

			if (this->peek().value == ">") {
				this->next();
			}
			else{
				throw error::compiler_exception(
					"Missing closing angle bracket for contained type",
					error_code::INVALID_TYPE_SYNTAX,
					this->current_token().line_number
				);
			}

			// give an error if the tuple is empty and a note if the tuple only has one subtype
			if (subtypes.empty()) {
				throw error::compiler_exception(
					"Tuples must list at least 1 contained type",
					error_code::INCOMPLETE_TYPE_ERROR,
					current_lex.line_number
				);
			}
			else if (subtypes.size() == 1) {
				error::compiler_note("Unnecessary tuple (contains only one element)", current_lex.line_number);
			}
		}
		else {
			// todo: appropriate exception
		}
	}
	// otherwise, if it does not have a contained type, it is either a different type (keyword) or struct (identifier)
	else if (current_lex.type == enumerations::lexeme_type::KEYWORD_LEX || current_lex.type == enumerations::lexeme_type::IDENTIFIER_LEX)
	{
		// if we have an int, but we haven't pushed back signed/unsigned, default to signed
		if (current_lex.value == "int") {
			// if our symbol doesn't have signed or unsigned, set, it must be signed by default
			if (!qualities.is_signed() && !qualities.is_unsigned()) {
				qualities.add_quality(enumerations::symbol_quality::SIGNED);
			}
		}

		// store the type name in our enumerations::primitive_type object
		new_var_type = type_deduction::get_type_from_string(current_lex.value);

		// if we have a struct, make a note of the name
		if (new_var_type == enumerations::primitive_type::STRUCT)
		{
			// if we didn't have a valid type name, but it was a keyword, then throw an exception -- the keyword used was not a valid type identifier
			if (current_lex.type == enumerations::lexeme_type::KEYWORD_LEX)
			{
				throw error::compiler_exception(("Invalid type specifier '" + current_lex.value + "'"), 0, current_lex.line_number);
			}

			struct_name = current_lex.value;
		}
	}
	else {
		throw error::compiler_exception(
			("'" + current_lex.value + "' is not a valid type name"),
			error_code::MISSING_IDENTIFIER_ERROR,
			current_lex.line_number
		);
	}

	// create the symbol type data; if we have a list of subtypes, we need to use a different constructor than other types
	data_type symbol_type_data;
	if (subtype_is_list) {
		symbol_type_data = data_type(new_var_type, subtypes, qualities);
	}
	else {
		symbol_type_data = data_type(new_var_type, new_var_subtype, qualities, array_length_exp, struct_name);
	}
	return symbol_type_data;
}

data_type parser::parse_subtype(const std::string& grouping_symbol)
{
	this->next();	// eat the opening grouping symbol

	// first, parse the type (which will handle prefixed qualities)
	data_type new_var_subtype;
	new_var_subtype = this->get_type(grouping_symbol);
	
	// since subtypes have no 'default values', parse postfixed qualities, if there are any
	if (this->peek().value == "&") {
		this->next();	// eat the ampersand

		symbol_qualities postfixed_qualities = this->get_postfix_qualities(grouping_symbol);
		new_var_subtype.add_qualities(postfixed_qualities);
	}

	// ensure an angle bracket follows our postfixed qualities and eat it
	if (this->peek().value == get_closing_grouping_symbol(grouping_symbol)) {
		this->next();
	} else {
		throw error::compiler_exception("Unclosed grouping symbol found", 0, this->current_token().line_number);
	}

	return new_var_subtype;
}

symbol_qualities parser::get_prefix_qualities(const std::string& grouping_symbol)
{
	symbol_qualities qualities;

	// loop until we don't have a quality token, at which point we should return the qualities object
	lexeme current = this->current_token();
	while (current.type == enumerations::lexeme_type::KEYWORD_LEX && !is_type(current.value)) {
		// get the current quality and add it to our qualities object
		try {
			qualities.add_quality(get_quality(current));
		} catch (std::string &offending_quality) {
			// catch the exception thrown by 'add quality' and throw a new one with a line number
			throw error::quality_conflict(offending_quality, current.line_number);
		}

		// advance the token position
		current = this->next();
	}

	return qualities;
}

symbol_qualities parser::get_postfix_qualities(const std::string& grouping_symbol)
{
	std::string closing_symbol;
	if (is_opening_grouping_symbol(grouping_symbol) || grouping_symbol == "<") {	// todo: include < in function?
		closing_symbol = get_closing_grouping_symbol(grouping_symbol);
	}
	else {
		closing_symbol = "";
	}

	symbol_qualities qualities;	// create our qualities vector; initialize to an empty vector

	// continue parsing our SymbolQualities until we hit a semicolon, at which point we will trigger the 'done' flag
	bool done = false;
	while (this->peek().type == enumerations::lexeme_type::KEYWORD_LEX) {
		lexeme quality_token = this->next();	// get the token for the quality
		enumerations::symbol_quality quality = this->get_quality(quality_token);	// use our 'get_quality' function to get the enumerations::symbol_quality based on the token

		// try adding our qualities, throw an error if there is a conflict
		try {
			qualities.add_quality(quality);
		} catch (error::compiler_exception &e) {
			throw error::quality_conflict(quality_token.value, quality_token.line_number);
		}
	}

	return qualities;
}

enumerations::symbol_quality parser::get_quality(lexeme quality_token)
{
	// Given a lexeme containing a quality, returns the appropriate member from enumerations::symbol_quality

	enumerations::symbol_quality to_return = enumerations::symbol_quality::NO_QUALITY;

	// ensure the token is a kwd
	if (quality_token.type == enumerations::lexeme_type::KEYWORD_LEX) {
		// Use the unordered_map to find the quality
		auto it = symbol_qualities::quality_strings.find(quality_token.value);
		
		if (it == symbol_qualities::quality_strings.end()) {
			throw error::compiler_exception("Invalid qualifier", error_code::EXPECTED_SYMBOL_QUALITY, quality_token.line_number);
		}
		else {
			to_return = it->second;
		}
	}
	else {
		throw error::compiler_exception("Invalid qualifier", error_code::EXPECTED_SYMBOL_QUALITY, quality_token.line_number);
	}

	return to_return;
}

enumerations::exp_operator parser::get_unary_operator(const std::string& s)
{
	using ops = enumerations::exp_operator;
	
	ops op;

	if (s == "+") {
		op = ops::UNARY_PLUS;
	}
	else if (s == "-") {
		op = ops::UNARY_MINUS;
	}
	else if (s == "$") {
		op = ops::ADDRESS;
	}
	else if (s == "*") {
		op = ops::DEREFERENCE;
	}
	else if (s == "not") {
		op = ops::NOT;
	}
	else if (s == "~") {
		op = ops::BIT_NOT;
	}
	else {
		op = ops::NO_OP;
	}
	
	return op;
}
