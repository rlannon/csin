#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>

#include "type_deduction.hpp"
#include "statements.hpp"
#include "expressions.hpp"
#include "lexer.hpp"

#include "../util/exceptions.hpp"	// error::compiler_exception
#include "../util/data_type.hpp"	// type information
#include "../util/general_utilities.hpp"
#include "../util/enumerated_types.hpp"

class parser
{
	// token trackers
	std::vector<lexeme> tokens;
	size_t position;
	size_t num_tokens;

	// the name of the file being parsed
	std::string filename;

	// Sentinel variable
	bool quit;

	// translates an operator character into an enumerations::exp_operator type
	static enumerations::exp_operator translate_operator(const std::string& op_string);
	static bool is_valid_copy_assignment_operator(enumerations::exp_operator op);
	static bool is_valid_move_assignment_operator(enumerations::exp_operator op);
	enumerations::exp_operator read_operator(bool peek);

	// our operator and precedence handlers
	static const std::unordered_map<enumerations::exp_operator, size_t> op_precedence;	// todo: create operator class
	static size_t get_precedence(const std::string& symbol, size_t line = 0);
	static size_t get_precedence(enumerations::exp_operator op, size_t line = 0);

	// Some utility functions
	bool is_at_end();	// tells us whether we have run out of tokens
	lexeme peek();	// get next token without moving the position
	lexeme next();	// get next token
	lexeme current_token();	// get token at current position
	lexeme previous();	// similar to peek; get previous token without moving back
	lexeme back();	// move backward one
	void skipPunc(char punc);	// skips the specified punctuation mark
	static bool is_type(const std::string& lex_value);
	static std::string get_closing_grouping_symbol(const std::string& beginning_symbol);
	static bool is_opening_grouping_symbol(const std::string& to_test);
	static bool has_return(const statement::statement_block& to_test);
	static enumerations::exp_operator get_unary_operator(const std::string& s);	// located in ParserUtil.cpp
	static bool is_valid_operator(lexeme l);

	// get the appropriate enumerations::symbol_quality member from the lexeme containing it
	static enumerations::symbol_quality get_quality(lexeme quality_token);

	// we have to fetch a type (and its qualities) more than once; use a tuple for this
	data_type get_type(const std::string& grouping_symbol = "");
	data_type parse_subtype(const std::string& grouping_symbol = "");
	symbol_qualities get_prefix_qualities(const std::string& grouping_symbol = "");
	symbol_qualities get_postfix_qualities(const std::string& grouping_symbol="");

	// Parsing statements -- each statement type will use its own function to return a statement of that type
	std::unique_ptr<statement::statement_base> parse_statement(const bool is_function_parameter = false);		// entry function to parse a statement

	std::unique_ptr<statement::statement_base> parse_include(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_declaration(lexeme current_lex, bool is_function_parameter = false);
	std::unique_ptr<statement::statement_base> parse_ite(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_allocation(lexeme current_lex, bool is_function_parameter = false);
	std::unique_ptr<statement::statement_base> parse_assignment(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_move(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_return(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_while(lexeme current_lex);

	// We have a few different types of definitions we could parse; delegate
	std::unique_ptr<statement::statement_base> parse_definition(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_function_definition(lexeme current_lex);
	std::unique_ptr<statement::statement_base> parse_struct_definition(lexeme current_lex);

	std::unique_ptr<statement::statement_base> parse_function_call(lexeme current_lex);

	// Parsing the body of a construction requires special consideration
	std::unique_ptr<statement::statement_base> parse_construction();
	std::unique_ptr<expression::construction> parse_construction_body(const bool has_type = false, const std::string& explicit_type = "");

	// Parsing expressions

	/*
	put default argument here because we call "parse_expression" in "maybe_binary"; as a reuslt, "his_prec" appears as if it is being passed to the next maybe_binary, but isn't because we parse an expression before we parse the binary, meaning my_prec gets set to 0, and not to his_prec as it should
	Note we also have a 'not_binary' flag here; if the expression is indexed, we may not want to have a binary expression parsed
	*/
	std::unique_ptr<expression::expression_base> parse_expression(
		const size_t prec=0,
		std::string grouping_symbol = "(",
		bool not_binary = false,
		const bool omit_equals = false,
		const bool allow_brace = false
	);
	inline std::unique_ptr<expression::expression_base> parse_expression(const bool allow_brace)
	{
		return parse_expression(0, "(", false, false, allow_brace);
	}

	std::unique_ptr<expression::expression_base> maybe_binary(
		std::unique_ptr<expression::expression_base> left,
		const size_t my_prec,
		const std::string& grouping_symbol = "(",
		const bool omit_equals = false,
		const bool allow_brace = false
	);	// check to see if we need to fashion a binary expression
	static enumerations::exp_operator get_compound_arithmetic_op(const enumerations::exp_operator op);
public:
	// our entry function
	statement::statement_block create_ast();

	parser(const std::string& filename);
	~parser();
};
