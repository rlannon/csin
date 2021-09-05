#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "enumerated_types.hpp"
#include "exceptions.hpp"

class symbol_qualities
{
	bool const_q;	// our qualities -- since almost all of these are reserved in C++, suffix with _q, for "quality"
	bool final_q;
	bool static_q;
	bool dynamic_q;
	bool signed_q;
    bool _listed_unsigned;
	bool long_q;
	bool short_q;
	bool extern_q;
    bool _managed;

	// function qualities -- for calling conventions, unused by other data
	// todo: create additional, inherited class 'function_symbol_qualities' to use with functions?
	bool sincall_con;
	bool c64_con;
	bool windows_con;
public:
	bool operator==(const symbol_qualities& right) const;
	bool operator!=(const symbol_qualities& right) const;

	static const std::unordered_map<std::string, enumerations::symbol_quality> quality_strings;

	bool is_const() const;	// accessors
	bool is_final() const;
	bool is_static() const;
	bool is_dynamic() const;
	bool is_signed() const;
	bool is_unsigned() const;
	bool is_long() const;
	bool is_short() const;
	bool is_extern() const;
    bool is_managed() const;

    bool has_sign_quality() const;

	// void add_qualities(std::vector<enumerations::symbol_quality> to_add);
	void add_qualities(symbol_qualities to_add);
    void add_quality(enumerations::symbol_quality to_add);

	symbol_qualities(std::vector<enumerations::symbol_quality> qualities);
	symbol_qualities(	bool is_const, 
						bool is_static, 
						bool is_dynamic, 
						bool is_signed, 
						bool is_long = false, 
						bool is_short = false, 
						bool is_extern = false	);
	symbol_qualities();
	~symbol_qualities();
};
