#pragma once

#include <string>

#include "../util/enumerated_types.hpp"

struct lexeme {
	enumerations::lexeme_type type;
	std::string value;
	unsigned int line_number;
	
	// overload the == operator so we can compare two lexemes
	bool operator==(const lexeme& b);

	lexeme();
	lexeme(const enumerations::lexeme_type type, const std::string& value, const unsigned int line_number);
};
