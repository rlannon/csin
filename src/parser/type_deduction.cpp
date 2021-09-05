#include "type_deduction.hpp"

enumerations::primitive_type type_deduction::get_type_from_lexeme(enumerations::lexeme_type lex_type)
{
	using pt = enumerations::primitive_type;
	using lt = enumerations::lexeme_type;

	switch (lex_type)
	{
	case lt::STRING_LEX:
		return pt::STRING;
	case lt::BOOL_LEX:
		return pt::BOOL;
	case lt::INT_LEX:
		return pt::INT;
	case lt::FLOAT_LEX:
		return pt::FLOAT;
	case lt::CHAR_LEX:
		return pt::CHAR;
	default:
		return pt::STRUCT;
	}
}

enumerations::primitive_type type_deduction::get_type_from_string(const std::string& candidate)
{
	for (size_t i = 0; i < num_types; i++)
	{
		if (candidate == type_strings[i])
		{
			// if we have a match, return it
			return types[i];
		}
		else
		{
			continue;
		}
	}

	return enumerations::primitive_type::STRUCT;
}

std::string type_deduction::get_string_from_type(enumerations::primitive_type candidate)
{
	for (size_t i = 0; i < num_types; i++)
	{
		if (candidate == types[i])
		{
			// if we have a match, return it
			return type_strings[i];
		}
		else
		{
			continue;
		}
	}

	return "struct";
}
