#pragma once

namespace enumerations
{
	/**< A list of possible lexeme types */
	enum lexeme_type {
		FLOAT_LEX,
		INT_LEX,
		STRING_LEX,
		CHAR_LEX,
		BOOL_LEX,
		IDENTIFIER_LEX,
		KEYWORD_LEX,
		PUNCTUATION,
		OPERATOR,
		ESCAPED,
		NULL_LEXEME
	};

	/**< A list of possible statement types */
	enum statement_type {
		STATEMENT_GENERAL,
		INCLUDE,
		DECLARATION,
		ALLOCATION,
		ASSIGNMENT,
		MOVEMENT,
		RETURN_STATEMENT,
		IF_THEN_ELSE,
		WHILE_LOOP,
		FUNCTION_DEFINITION,
		STRUCT_DEFINITION,
		CALL,
		INLINE_ASM,
		FREE_MEMORY,
		SCOPED_BLOCK,
		CONSTRUCTION_STATEMENT,
		COMPOUND_ASSIGNMENT
	};

	/**< A list of possible expression types */
	enum expression_type {
		EXPRESSION_GENERAL,
		LITERAL,	// can be a literal int (e.g., 5), a literal float (e.g., 1.2), a literal string (e.g., "hello"), a literal bool (true/false) ...
		IDENTIFIER,		// any named data
		LIST,	// initializer-lists, mostly; syntax is { ... , ... }
		INDEXED,
		BINARY,
		UNARY,
		CALL_EXP,
		CAST,
		ATTRIBUTE,
		KEYWORD_EXP,
		CONSTRUCTION_EXP,
		PROC_EXP
	};

	/**< A list of available attributes */
	enum attribute {
		NO_ATTRIBUTE,
		LENGTH,
		SIZE,
		VARIABILITY
	};

	/**< So that we know whether a symbol is a variable, function definition, struct definition, etc. */
	enum symbol_type {
		VARIABLE,
		FUNCTION_SYMBOL,
		STRUCT_SYMBOL
	};

	/**< Defined so that the symbol's quality does not need to be stored as a string */
	enum symbol_quality {
		NO_QUALITY,
		CONSTANT,
		FINAL,
		STATIC,
		DYNAMIC,
		SIGNED,
		UNSIGNED,
		LONG,
		SHORT,
		SINCALL_CONVENTION,
		C64_CONVENTION,
		WINDOWS_CONVENTION,
		EXTERN,
		UNMANAGED
	};

	/**< A list of available operators */
	enum exp_operator {
		COPY_ASSIGN,	// the = operator
		RIGHT_ARROW,	// the -> operator
		LEFT_ARROW,	// the <- operator
		PLUS_EQUAL,	// +=
		MINUS_EQUAL,	// -=
		MULT_EQUAL,	// *=
		DIV_EQUAL,	// /=
		MOD_EQUAL,	// %=
		AND_EQUAL,	// &=
		OR_EQUAL,	// |=
		XOR_EQUAL,	// ^=
		LEFT_SHIFT_EQUAL,	// <<=
		RIGHT_SHIFT_EQUAL,	// >>=
		PLUS,
		MINUS,
		UNARY_PLUS,
		UNARY_MINUS,
		MULT,
		DIV,
		EQUAL,
		NOT_EQUAL,
		GREATER,
		LESS,
		GREATER_OR_EQUAL,
		LESS_OR_EQUAL,
		AND,	// 'AND' is logical-AND (C++ &&) -- Python keyword 'and'
		NOT,	// logical not
		OR,		// logical or
		XOR,	// logical xor
		MODULO,
		BIT_AND,	// 'BIT_AND' is bitwise-AND (C++ &) -- operator '&'
		BIT_OR,		// same goes with BIT_OR
		BIT_XOR,	// same with BIT_XOR
		BIT_NOT,	// same with BIT_NOT
		LEFT_SHIFT,
		RIGHT_SHIFT,
		DOT,	// the . operator
		INDEX,	// square brackets for indexing
		ADDRESS,		// $
		DEREFERENCE,	// *
		TYPECAST,	// the 'as' operator
		ATTRIBUTE_SELECTION,	// :
		CONTROL_TRANSFER,	// @, used in function calls
		PROC_OPERATOR,  // (), marks a procedure
		SCOPE_RESOLUTION,	//	::
		NO_OP
	};

	enum primitive_type {
		// So that our types are all clearly defined
		NONE,
		CHAR,
		INT,
		FLOAT,
		STRING,
		BOOL,
		VOID,
		PTR,
		REFERENCE,
		RAW,
		ARRAY,
		STRUCT,
		TUPLE
	};
} /* namespace enumerations */
