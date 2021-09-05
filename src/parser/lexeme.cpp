#include "lexeme.hpp"

bool lexeme::operator==(const lexeme& b) {
    // allow lexemes to be compared with the == operator
	// note that we don't care about the line number; we only want to know if they have the same type/value pair
	return ((this->type == b.type) && (this->value == b.value));
}

lexeme::lexeme()
    : line_number(0) { }

lexeme::lexeme( const enumerations::lexeme_type type,
                const std::string& value,
                const unsigned int line_number)
    : type(type)
    , value(value)
    , line_number(line_number) { }
