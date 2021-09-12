#pragma once

#include <vector>
#include <string>
#include <array>
#include <unordered_map>

#include "enumerated_types.hpp"
#include "exceptions.hpp"

class symbol_qualities
{
	static constexpr std::array<char, 10> _decorations{
		'c', 'f', 'a', 'd', 'g', 'l', 's', 'e', 'u', 'm'
	};
	std::array<bool, _decorations.size()> _qualities;

	static constexpr size_t _const_index{0};
	static constexpr size_t _final_index{1};
	static constexpr size_t _static_index{2};
	static constexpr size_t _dynamic_index{3};
	static constexpr size_t _signed_index{4};
	static constexpr size_t _listed_unsigned_index{5};
	static constexpr size_t _long_index{6};
	static constexpr size_t _short_index{7};
	static constexpr size_t _extern_index{8};
	static constexpr size_t _managed_index{9};

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

	void add_qualities(symbol_qualities to_add);
    void add_quality(enumerations::symbol_quality to_add);

	std::string decorate() const; 

	symbol_qualities(std::vector<enumerations::symbol_quality> qualities);
	symbol_qualities(	bool is_const, 
						bool is_static, 
						bool is_dynamic, 
						bool is_signed, 
						bool is_long = false, 
						bool is_short = false, 
						bool is_extern = false	);
	symbol_qualities(const symbol_qualities& other);
	symbol_qualities();
	~symbol_qualities();
};
