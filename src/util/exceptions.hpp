#pragma once

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <bitset>

#include "error_codes.hpp"


// todo: include file information in exception
namespace error
{
	class compiler_exception : public std::exception
	{
	protected:
		std::string message;
		unsigned int code;
		unsigned int line;
	public:
		explicit compiler_exception(const std::string& message, const unsigned int code = 0, const unsigned int line = 0);
		void set_line(unsigned int new_line);
		virtual const char* what() const noexcept;
	};

	class variable_array_length: public compiler_exception
	{
	public:
		explicit variable_array_length(unsigned int line);
	};

	class invalid_member_selection: public compiler_exception
	{
	public:
		explicit invalid_member_selection(unsigned int line);
	};

	class illegal_operation : public compiler_exception
	{
	public:
		explicit illegal_operation(unsigned int line);
	};

	class illegal_return : public compiler_exception
	{
	public:
		explicit illegal_return(unsigned int line);
	};

	class no_return : public compiler_exception
	{
	public:
		explicit no_return(unsigned int line);
	};

	class symbol_not_found : public compiler_exception
	{
	public:
		explicit symbol_not_found(unsigned int line);
	};

	class duplicate_symbol : public compiler_exception
	{
	public:
		explicit duplicate_symbol(unsigned int line);
	};

	class not_an_lvalue : public compiler_exception
	{
	public:
		explicit not_an_lvalue(unsigned int line);
	};

	class referenced_before_initialization : public compiler_exception
	{
	public:
		explicit referenced_before_initialization(std::string symbol_name, unsigned int line);
	};

	class undefined : public compiler_exception
	{
	public:
		explicit undefined(unsigned int line);
	};

	class signature_mismatch : public compiler_exception
	{
	public:
		explicit signature_mismatch(unsigned int line);
	};

	class invalid_symbol : public compiler_exception
	{
	public:
		explicit invalid_symbol(unsigned int line);
	};

	class out_of_scope : public compiler_exception
	{
	public:
		explicit out_of_scope(unsigned int line);
	};

	class unexpected_declaration : public compiler_exception
	{
	public:
		explicit unexpected_declaration(unsigned int line);
	};

	class type_error : public compiler_exception
	{
	public:
		explicit type_error(unsigned int line);
	};

	class quality_conflict : public compiler_exception
	{
	public:
		explicit quality_conflict(std::string &conflicting_quality, unsigned int line);
	};

	class illegal_quality : public compiler_exception
	{
	public:
		explicit illegal_quality(std::string &offending_quality, unsigned int &line);
	};

	class invalid_type : public compiler_exception
	{
	public:
		explicit invalid_type(unsigned int line);
	};

	class mutability_violation : public compiler_exception
	{
	public:
		explicit mutability_violation(unsigned int line);
	};

	class illegal_type_demotion : public compiler_exception
	{
	public:
		explicit illegal_type_demotion(unsigned int line);
	};

	class illegal_void : public compiler_exception
	{
	public:
		explicit illegal_void(unsigned int line);
	};

	class illegal_unary_operator : public compiler_exception
	{
	public:
		explicit illegal_unary_operator(unsigned int line);
	};

	class undefined_operator : public compiler_exception
	{
	public:
		explicit undefined_operator(std::string op, unsigned int line);
	};

	class const_assignment : public compiler_exception
	{
	public:
		explicit const_assignment(unsigned int line);
	};

	class final_assignment : public compiler_exception
	{
	public:
		explicit final_assignment(unsigned int line);
	};

	class const_definition : public compiler_exception
	{
	public:
		explicit const_definition(unsigned int line);
	};

	class ConstInitializationException : public compiler_exception
	{
	public:
		explicit ConstInitializationException(unsigned int line);
	};

	class illegal_typecast : public compiler_exception
	{
	public:
		explicit illegal_typecast(unsigned int line);
	};

	class illegal_indirection : public compiler_exception
	{
	public:
		explicit illegal_indirection(unsigned int line);
	};

	class type_not_subscriptable : public compiler_exception
	{
	public:
		explicit type_not_subscriptable(unsigned int line);
	};

	// todo: allow warning and note codes?

	// sometimes, we want to print an error message, but we don't need to stop compilation
	void compiler_warning(std::string message, unsigned int code, unsigned int line = 0);
	void half_precision_not_supported_warning(unsigned int line);

	// sometimes, we want to print a note rather than an error
	void compiler_note(std::string message, unsigned int line = 0);

	class illegal_token : public compiler_exception
	{
	public:
		explicit illegal_token(std::string offending_token, unsigned int line);
	};

	class incomplete_type : public compiler_exception
	{
	public:
		explicit incomplete_type(const unsigned int &line);
	};

	class expected_semicolon : public compiler_exception
	{
	public:
		explicit expected_semicolon(const unsigned int &line);
	};

	class missing_identifier : public compiler_exception
	{
	public:
		explicit missing_identifier(const unsigned int &line);
	};

	class imbalanced_grouping : public compiler_exception
	{
	public:
		explicit imbalanced_grouping(const unsigned int &line);
	};

	class unexpected_keyword : public compiler_exception
	{
	public:
		explicit unexpected_keyword(std::string &offending_keyword, const unsigned int &line);
	};

	class invalid_call_syntax : public compiler_exception
	{
	public:
		explicit invalid_call_syntax(const unsigned int &line);
	};

	// like in the compiler, we sometimes want to print warnings without stopping parsing
	void parser_warning(std::string message, unsigned int line_number = 0);
}	/* namespace error */
