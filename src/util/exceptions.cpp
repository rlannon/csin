#include "exceptions.hpp"

namespace error
{
	const char* compiler_exception::what() const noexcept {
		return message.c_str();
	}

	void compiler_exception::set_line(unsigned int new_line) {
		this->line = new_line;
	}

	compiler_exception::compiler_exception(
		const std::string& message,
		const unsigned int code,
		const unsigned int line
	) 
		: message(message)
		, code(code)
		, line(line) {
		this->message = "**** Compiler error C" + std::to_string(this->code) + ": " + this->message + " (error occurred at or near line " + std::to_string(this->line) + ")";
	}

	variable_array_length::variable_array_length(unsigned int line):
	compiler_exception(
		"Array length must be an integer constant or declared as 'dynamic'; use a literal or 'constexpr'",
		error_code::UNKNOWN_LENGTH_ERROR,
		line
	) {
		// super called
	}

	invalid_member_selection::invalid_member_selection(unsigned int line):
		compiler_exception(
			"Invalid operator in member selection expression",
			error_code::INVALID_EXPRESSION_TYPE_ERROR,
			line
		)
	{
		// super called
	}

	illegal_operation::illegal_operation(unsigned int line):
		compiler_exception("This operation is not allowed here", error_code::ILLEGAL_OPERATION_ERROR, line)
	{
		// super called
	}

	illegal_return::illegal_return(unsigned int line):
	compiler_exception(
		"Return statement not allowed here; they may only occur inside functions",
		error_code::ILLEGAL_RETURN_ERROR,
		line
	) {
		// super called
	}

	no_return::no_return(unsigned int line) :
		compiler_exception(
			"Return statement not found in function (perhaps not all control paths return a value?)",
			error_code::NO_RETURN_ERROR,
			line
		)
	{
		// super called
	}

	symbol_not_found::symbol_not_found(unsigned int line) :
		compiler_exception("Could not find referenced symbol", error_code::SYMBOL_NOT_FOUND_ERROR, line)
	{
		// we don't need a function body because we called the super constructor
	}

	duplicate_symbol::duplicate_symbol(unsigned int line) :
		compiler_exception("Symbol already defined in this scope", error_code::DUPLICATE_SYMBOL_ERROR, line)
	{
		// function body not necessary (super called)
	}

	undefined::undefined(unsigned int line) :
		compiler_exception("Undefined reference to object", error_code::UNDEFINED_ERROR, line)
	{
		// function body not necessary (super called)
	}

	signature_mismatch::signature_mismatch(unsigned int line) :
		compiler_exception("Function call does not match function signature", error_code::SIGNATURE_ERROR, line)
	{
		// body not necessary (super called)
	}

	invalid_symbol::invalid_symbol(unsigned int line) :
		compiler_exception("Found a symbol, but it was of the improper type (e.g., VARIABLE instead of FUNCTION)", error_code::INVALID_SYMBOL_TYPE_ERROR, line)
	{
		/*
		Since all symbols use the same table, we can't have conflicting names between functions and variables.
		If a symbol is found, but the symbol is not a function, then we have an error.
		*/
	}

	out_of_scope::out_of_scope(unsigned int line) :
		compiler_exception("Symbol is out of scope", error_code::OUT_OF_SCOPE_ERROR, line)
	{
		// No body necessary
	}

	unexpected_declaration::unexpected_declaration(unsigned int line) :
	compiler_exception(
		"Declarations must be made in the global scope",
		error_code::DECLARATION_ERROR,
		line
	) {

	}

	type_error::type_error(unsigned int line) :
		compiler_exception("Types are not compatible", error_code::TYPE_ERROR, line)
	{
		// Exception should be used when types are incompatible
	}

	quality_conflict::quality_conflict(const std::string& conflicting_quality, unsigned int line) :
		compiler_exception(
			(
				"Symbol quality '" + conflicting_quality + "' may not be used here (there is a conflicting quality present)"),
				error_code::QUALITY_CONFLICT_ERROR, 
				line
			)
	{
		// Body not necessary (super called)
	}

	illegal_quality::illegal_quality(const std::string& offending_quality, unsigned int line) :
	compiler_exception(
		("Illegal symbol quality '" + offending_quality + "'"),
		error_code::ILLEGAL_QUALITY_ERROR,
		line
	) {
		// super called
	}

	invalid_type::invalid_type(unsigned int line) :
		compiler_exception(
			"Type was parsed correctly, but violates SIN's type validity policy",
			error_code::TYPE_VALIDITY_RULE_VIOLATION_ERROR,
			line
		)
	{
		// super called
	}

	mutability_violation::mutability_violation(unsigned int line) :
		compiler_exception(
			"enumerations::primitive_type variability policy violation",
			error_code::VARIABILITY_ERROR,
			line
		) {
		// super called
	}

	illegal_type_demotion::illegal_type_demotion(unsigned int line) :
		compiler_exception(
			"Cannot demote right-hand type to less restrictive variability quality",
			error_code::VARIABILITY_ERROR,
			line
	) {
		// super called
	}

	illegal_void::illegal_void(unsigned int line) :
		compiler_exception("Void type cannot be used in expression of this type", error_code::VOID_TYPE_ERROR, line)
	{
		// Exception should be used when 'void' type was found, but cannot be used here
	}

	illegal_unary_operator::illegal_unary_operator(unsigned int line) :
	compiler_exception(
		"Invalid unary operator",
		error_code::INVALID_UNARY_OPERATOR_ERROR,
		line
	) {
		// super called
	}

	const_assignment::const_assignment(unsigned int line) :
		compiler_exception("Cannot make assignment to const-qualified variable", error_code::CONST_ASSIGNMENT_ERROR, line)
	{
		// we don't need a function body because we called the super constructor
	}

	final_assignment::final_assignment(unsigned int line) :
	compiler_exception(
		"Cannot make assignment to initialized final-qualified variable",
		error_code::FINAL_ASSIGNMENT_ERROR,
		line
	) {
		// super called
	}

	const_definition::const_definition(unsigned int line) :
		compiler_exception(
			"Constants must be initialized in their allocation",
			error_code::CONST_ALLOCATION_ERROR,
			line
		) {
		// super called
	}

	ConstInitializationException::ConstInitializationException(unsigned int line) :
	compiler_exception(
		"Constanst must be initialized with a compile-time constant",
		error_code::NON_CONST_VALUE_ERROR,
		line
	) {
		// super called
	}

	illegal_typecast::illegal_typecast(unsigned int line) :
		compiler_exception(
			"Illegal typecast",
			error_code::INVALID_CAST_ERROR,
			line
		)
	{
			// super called
	}

	illegal_indirection::illegal_indirection(unsigned int line) :
	compiler_exception(
		"Illegal indirection; must have pointer type",
		error_code::ILLEGAL_INDIRECTION,
		line
	) {
		// super called
	}

	type_not_subscriptable::type_not_subscriptable(unsigned int line) :
	compiler_exception(
		"enumerations::primitive_type not subscriptable",
		error_code::NOT_SUBSCRIPTABLE_ERROR,
		line
	) {
		// super called
	}

	// Warnings and notes

	void compiler_warning(std::string message, unsigned int code, unsigned int line_number) {
		std::cout << "**** Compiler Warning W" << code << ": " << message << " (at or near line " << line_number << ")" << std::endl;
	}

	void half_precision_not_supported_warning(unsigned int line) {
		compiler_warning(
			"Found unsupported 16-bit half-precision floating point number; utilizing 32-bit single-precision instead",
			error_code::DATA_WIDTH_ERROR,
			line
		);
	}

	void compiler_note(std::string message, unsigned int line_number) {
		std::cout << "**** Note: " << message << " (line " << line_number << ")" << std::endl;
	}

	void parser_warning(std::string message, unsigned int line_number)
	{
		std::cout << "**** parser Warning: " << message << " (line " << line_number << ")" << std::endl;
	}

	illegal_token::illegal_token(
		std::string offending_token,
		unsigned int line
	) : error::compiler_exception(
		("Invalid token '" + offending_token + "' found while parsing"),
		error_code::INVALID_TOKEN,
		line
	) {
		// super called
	}

	incomplete_type::incomplete_type(const unsigned int line):
		error::compiler_exception(
			"Incomplete type information",
			error_code::INCOMPLETE_TYPE_ERROR,
			line
		)
	{
		// super called
	}

	expected_semicolon::expected_semicolon(const unsigned int& line) : error::compiler_exception("Syntax error; expected ';'", error_code::MISSING_SEMICOLON_ERROR, line) {

	}

	missing_identifier::missing_identifier(const unsigned int line) :
	error::compiler_exception(
		"Expected identifier",
		error_code::MISSING_IDENTIFIER_ERROR,
		line
	) {
		// super called
	}

	unexpected_keyword::unexpected_keyword(const std::string& offending_keyword, const unsigned int line) :
		error::compiler_exception(
			("Unexpected keyword '" + offending_keyword + "'"),
			error_code::UNEXPECTED_KEYWORD_ERROR,
			line
		)
	{
		// Used when a keyword is found, but one is not expected
	}

	imbalanced_grouping::imbalanced_grouping(const unsigned int line) :
	error::compiler_exception(
		"Syntax error; unclosed grouping symbol",
		error_code::MISSING_GROUPING_SYMBOL_ERROR,
		line
	) {
		// super called
	}

	invalid_call_syntax::invalid_call_syntax(const unsigned int line):
		error::compiler_exception(
			"Expected parens enclosing arguments in function call",
			error_code::MISSING_GROUPING_SYMBOL_ERROR,
			line
		)
	{
		// super called
	}

	undefined_operator::undefined_operator(std::string op, unsigned int line) :
		compiler_exception(
			"The " + op + " operator is undefined for this data type",
			line
		)
	{
		// super called
	}

	not_an_lvalue::not_an_lvalue(unsigned int line) :
		compiler_exception(
			"Left-hand side of assignment must be a modifiable-lvalue",
			error_code::NON_MODIFIABLE_LVALUE_ERROR,
			line
		)
	{
		// super called
	}

	referenced_before_initialization::referenced_before_initialization(std::string symbol_name, unsigned int line) :
		compiler_exception(
			"Symbol '" + symbol_name + "' referenced before assignment",
			error_code::REFERENCED_BEFORE_ASSIGNMENT_ERROR,
			line
		)
	{
		// super called
	}
}
