#include "parser.hpp"

statement::statement_block parser::create_ast() {
	/*

	create_ast
	Creates an abstract syntax tree based on a list of tokens

	Create an abstract syntax tree using parser::tokens. This is used not only as the entry function to the parser, but whenever an AST is needed as part of a statement.
	For example, a "Definition" statement requires an AST as one of its members; parse_top() is used to genereate the function's procedure's AST.

	*/

	// allocate a statement::statement_block, which will be used to store our AST
	statement::statement_block prog = statement::statement_block();

	// creating an empty lexeme will allow us to test if the current token has nothing in it
	// sometimes, the lexer will produce a null lexeme, so we want to skip over it if we find one
	lexeme null_lexeme(enumerations::lexeme_type::NULL_LEXEME, "", 0);

	// Parse a token file
	// While we are within the program and we have not reached the end of a procedure block, keep parsing
	while (!this->is_at_end() && !this->quit && (this->peek().value != "}") && (this->current_token().value != "}")) {
		// skip any semicolons and newline characters, if there are any in the tokens list
		this->skipPunc(';');
		this->skipPunc('\n');

		// if we encounter a null lexeme, skip it
		while (this->current_token() == null_lexeme) {
			this->next();
		}

		// Parse a statement
		std::shared_ptr<statement::statement_base> next = this->parse_statement();

		// check to see if it is a return statement; function definitions require them, but they are forbidden outside of them
		if (next->get_statement_type() == enumerations::statement_type::RETURN_STATEMENT) {
			prog.has_return = true;
		}

		// push the statement back
		prog.statements_list.push_back(next);

		// check to see if we are at the end now that we have advanced through the tokens list; if not, continue; if so, do nothing and the while loop will abort and return the AST we have produced
		if (!this->is_at_end() && !(this->peek().value == "}")) {
			this->next();
		}
	}

	// return the AST
	return prog;
}


parser::parser(const std::string& filename)
	: filename(filename) 
{
	// create a lexer
	std::ifstream infile;
	infile.open(filename, std::ios::in);
	lexer lexer(infile);

	// Tokenize the file
	std::cout << "Lexing..." << std::endl;
	while (!lexer.eof() && !lexer.exit_flag_is_set()) {
		lexeme token = lexer.read_next();

		// only push back tokens that aren't empty
		if (
			(token.type != enumerations::lexeme_type::NULL_LEXEME) &&
			(token.line_number != 0)
		) {
			this->tokens.push_back(token);
		}
		else {
			continue;
		}
	}

	this->quit = false;
	this->position = 0;
	this->num_tokens = parser::tokens.size();
}

parser::~parser() { }
