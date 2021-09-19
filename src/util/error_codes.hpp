#pragma once

namespace error_code {
    // Illegal operations
    constexpr unsigned int UNSUPPORTED_ERROR = 0;
    constexpr unsigned int CONST_ASSIGNMENT_ERROR = 1; /**< An operation tried to use `const` data as an lvalue. */
    constexpr unsigned int FINAL_ASSIGNMENT_ERROR = 2; /**< An operation tried to use `final` data as an lvalue. */
    constexpr unsigned int DATA_WIDTH_ERROR = 3; /**< There was a mismatch in the widths between two objects. */
    constexpr unsigned int OUT_OF_BOUNDS = 4; /**< An index went beyond the bounds of a given object. */
    constexpr unsigned int UNKNOWN_LENGTH_ERROR = 5; /**< The length of a non-dynamic array was not given at compile-time. */
    constexpr unsigned int MOVE_TO_REFERENCE_ERROR = 7;
    
    constexpr unsigned int ALLOC_INIT_REQUIRED = 10; /**< The specified type requires alloc-init syntax, but was not used. */
	constexpr unsigned int CONST_ALLOCATION_ERROR = 11;	/**< `const` data was not initialized in its allocation. */
    constexpr unsigned int NON_CONST_VALUE_ERROR = 12; /**< Attempted to initialize `const` data with non-`const` data. */
    constexpr unsigned int REFERENCE_ALLOCATION_ERROR = 13; /**< A reference was not initialized in its allocation. */
    constexpr unsigned int STATIC_MEMORY_INITIALIZATION_ERROR = 15;
    
    constexpr unsigned int DUPLICATE_SYMBOL_ERROR = 30; /** The symbol already exists in that scope; it cannot be redefined. */
	constexpr unsigned int DUPLICATE_DEFINITION_ERROR = 31;	/**< The definition for this resource was already found. */
	
    constexpr unsigned int NON_MODIFIABLE_LVALUE_ERROR = 40;	/**< Left-hand expressions in assignments must be modifiable-lvalues. */
	constexpr unsigned int REFERENCED_BEFORE_ASSIGNMENT_ERROR = 41;	/** All symbols must be assigned before they can be referenced safely. */
    
    constexpr unsigned int ILLEGAL_OPERATION_ERROR = 50;    /** The statement is not allowed where it was found. */
    constexpr unsigned int ILLEGAL_RETURN_ERROR = 51;   // Return statements must only occur within functions. */
	constexpr unsigned int NO_RETURN_ERROR = 52;	/** A function must return a value in all possible control paths. */
    constexpr unsigned int RETURN_AUTOMATIC_REFERENCE = 53; /** A function attempted to return a reference to automatic memory. */

    constexpr unsigned int INVALID_UNARY_OPERATOR_ERROR = 55;   /**< This operator may not be used as a unary operator. */
    constexpr unsigned int UNARY_TYPE_NOT_SUPPORTED = 56;   /**< The unary operator given is not defined for the type found. */
	constexpr unsigned int UNDEFINED_OPERATOR_ERROR = 57;	/**< The operator is undefined for the given data type. */
    
    constexpr unsigned int ILLEGAL_ADDRESS_OF_ARGUMENT = 61;    /**< The address-of operator may only be used with lvalues and member selection binary expressions. */
    constexpr unsigned int ILLEGAL_INDIRECTION = 62;    /** The dereference (`*`) operator may only be used with pointer types. */
    constexpr unsigned int ILLEGAL_THIS_PARAMETER = 65;

    constexpr unsigned int SELF_CONTAINMENT_ERROR = 71; /**< A struct may not contain an instance of itself. */

    constexpr unsigned int CONSTRUCTION_NUMBER_INIT_ERROR = 80; /**< Constructions must initialize each member exactly once. */
    
    // Location / definition errors
    constexpr unsigned int SYMBOL_NOT_FOUND_ERROR = 100;
    constexpr unsigned int UNDEFINED_ERROR = 101;
    constexpr unsigned int UNDEFINED_STRUCT_ACCESSION = 102;
    constexpr unsigned int UNKNOWN_ATTRIBUTE = 103;
    constexpr unsigned int DATA_FREED = 105;
    
    constexpr unsigned int EMPTY_SCOPE_BLOCK = 111;
    
    constexpr unsigned int SIGNATURE_ERROR = 120;
    
    constexpr unsigned int OUT_OF_SCOPE_ERROR = 150;
    
    constexpr unsigned int DECLARATION_ERROR = 160;
    constexpr unsigned int INCLUDE_SCOPE_ERROR = 165;
    constexpr unsigned int FILE_NOT_FOUND_ERROR = 166;
    
    constexpr unsigned int CALLING_CONVENTION_ERROR = 170;
    
    constexpr unsigned int INVISIBLE_SYMBOL = 180;  // see docs/Includes.md

    // enumerations::primitive_type errors
    constexpr unsigned int INVALID_SYMBOL_TYPE_ERROR = 200;
    constexpr unsigned int UNEXPECTED_FUNCTION_SYMBOL = 203;
    constexpr unsigned int UNICODE_ERROR = 205;
    
    constexpr unsigned int TYPE_ERROR = 210;
    constexpr unsigned int VOID_TYPE_ERROR = 211;
    constexpr unsigned int OPERATOR_TYPE_ERROR = 212;   /**< The specified operator could not be used on the given expression. */
    constexpr unsigned int INVALID_CAST_ERROR = 213;
    constexpr unsigned int NOT_SUBSCRIPTABLE_ERROR = 214;   /**< The subscript (`[]`) operator is reserved for arrays. */
    constexpr unsigned int RETURN_MISMATCH_ERROR = 215; /**< The function's return type does not match its signature. */
    constexpr unsigned int INCORRECT_THIS_TYPE = 219;

	constexpr unsigned int TYPE_VALIDITY_RULE_VIOLATION_ERROR = 220;	/** The type given violated SIN's type rules. */
	constexpr unsigned int STRUCT_TYPE_EXPECTED_ERROR = 225;	/**< To use the dot operator, the left-hand expression must be 'struct' type. */
    constexpr unsigned int ILLEGAL_STRUCT_NAME = 226;

    constexpr unsigned int QUALITY_CONFLICT_ERROR = 230;
    constexpr unsigned int ILLEGAL_QUALITY_ERROR = 231;
	constexpr unsigned int VARIABILITY_ERROR = 232;
	constexpr unsigned int TYPE_MANAGEMENT_ERROR = 235;

    constexpr unsigned int SIGNED_UNSIGNED_MISMATCH = 241;
    constexpr unsigned int WIDTH_MISMATCH = 242;
    constexpr unsigned int POTENTIAL_DATA_LOSS = 243;

    constexpr unsigned int SIGNATURE_MISMATCH = 250;
    constexpr unsigned int LIST_TYPE_MISMATCH = 253;

    constexpr unsigned int DEDUCATION_FAILURE = 290;
    constexpr unsigned int TEMPLATE_TYPE_DEDUCTION_FAILURE = 291;
    constexpr unsigned int CONSTRUCTION_TYPE_DEDUCTION_FAILURE = 292;

    // Internal errors, etc.
    constexpr unsigned int INVALID_EXPRESSION_TYPE_ERROR = 300;
    constexpr unsigned int TUPLE_MEMBER_SELECTION_ERROR = 301;
    constexpr unsigned int STRUCT_MEMBER_SELECTION_ERROR = 302;

    constexpr unsigned int ILLEGAL_MOVE_ASSIGNMENT_EXPRESSION = 310;

    constexpr unsigned int UNSUPPORTED_FEATURE = 390;

    // Parse errors
    constexpr unsigned int INVALID_TOKEN = 400;
    constexpr unsigned int BAD_LITERAL = 401;
    constexpr unsigned int EXPECTED_SYMBOL_QUALITY = 402;
    constexpr unsigned int MISSING_SEMICOLON_ERROR = 404;
    constexpr unsigned int MISSING_GROUPING_SYMBOL_ERROR = 405;
    constexpr unsigned int MISSING_IDENTIFIER_ERROR = 406;
    constexpr unsigned int INVALID_TYPE_SYNTAX = 407;
    constexpr unsigned int UNEXPECTED_KEYWORD_ERROR = 410;
    constexpr unsigned int UNEXPECTED_SYMBOL_QUALITY = 412;

    constexpr unsigned int EXPECTED_INITIALIZATION = 421;
    constexpr unsigned int EXPECTED_LIST_INITIALIZATION = 422;
    
    constexpr unsigned int INCOMPLETE_TYPE_ERROR = 430; /**< The given type information was incomplete and could not be parsed. */

    // Warning codes
    constexpr unsigned int UNSAFE_OPERATION = 501;
    constexpr unsigned int BITSHIFT_RESULT = 502;

    constexpr unsigned int MAIN_SIGNATURE = 510;    /** 'main' should return an `int` and have one argument, `dynamic array<string> args`. */

    // Note codes (not necessarily warnings, but alerts)
    constexpr unsigned int NO_EFFECT = 900; /** The statement has no observable effect. */
};
