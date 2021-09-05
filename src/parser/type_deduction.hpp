#pragma once

#include "../util/enumerated_types.hpp"

#include <cinttypes>
#include <string>
#include <array>

namespace type_deduction {
    // data members
	const size_t num_types = 10;
    const std::array<std::string, num_types> type_strings{ 
        "char", "int", "float", "string", "bool", "void", "ptr", "raw", "array", "struct"
    };
    const std::array<enumerations::primitive_type, num_types> types{
        enumerations::primitive_type::CHAR,
        enumerations::primitive_type::INT,
        enumerations::primitive_type::FLOAT,
        enumerations::primitive_type::STRING,
        enumerations::primitive_type::BOOL,
        enumerations::primitive_type::VOID,
        enumerations::primitive_type::PTR,
        enumerations::primitive_type::RAW,
        enumerations::primitive_type::ARRAY,
        enumerations::primitive_type::STRUCT
    };

    // functions
	enumerations::primitive_type get_type_from_lexeme(enumerations::lexeme_type lex_type);
	enumerations::primitive_type get_type_from_string(const std::string& candidate);
    std::string get_string_from_type(enumerations::primitive_type candidate);
}
