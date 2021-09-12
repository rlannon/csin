#pragma once

#include <vector>
#include <memory>
#include <pair>
#include <cinttypes>
#include <cstdlib>

#include "data_widths.hpp"
#include "enumerated_types.hpp"
#include "exceptions.hpp"
#include "symbol_qualities.hpp"
#include "../parser/expression/expression.hpp"

class data_type
{
	static const std::unordered_map<
		const enumerations::primitive_type,
		const std::string
	> _type_strings;

	enumerations::primitive_type primary;	// always has a primary type
	std::vector<data_type> contained_types;	// tuples can have multiple contained types; will be empty if no subtype exists

	symbol_qualities qualities;	// the qualities of the symbol (const, signed, etc.)
	size_t array_length;	// if it's an array, track the length
	size_t width;	// the width (in bytes) of the type

	std::shared_ptr<expression::expression_base> array_length_expression;

	std::string struct_name;	// if the data type is 'struct', we need to know its name so we can look it up in the struct table

	/**
	 * Sets the width of the data_type object based on its type and qualities
	 * 
	 * Note that this function will not set the type width to PTR_WIDTH for dynamic types; 
	 * it will use the regular width, and the compiler will adjust for dynamic types where needed.
	 */
	void set_width();
	/**
	 * Sets the _must_free member, indicating whether this data type must be freed
	 * 
	 * Note this will add array or tuple types if a contained type must be freed.
	 * This will be handled by the compiler.
	 */
    void set_must_free();

    bool _must_free;
public:
	/**
	 * Ensures that type promotion rules are not broken
	 */
	static const bool is_valid_type_promotion(const symbol_qualities& left, const symbol_qualities& right);
	/**
	 * Checks to ensure the data_type object follows all of SIN's type rules
	 */
	static bool is_valid_type(const data_type &t);

	data_type& operator=(const data_type &right);

	bool operator==(const data_type& right) const;
	bool operator!=(const data_type& right) const;

	bool operator==(const enumerations::primitive_type right) const;
	bool operator!=(const enumerations::primitive_type right) const;

	enumerations::primitive_type get_primary() const;
	data_type get_subtype() const;
	const std::vector<data_type>& get_contained_types() const;
	std::vector<data_type>& get_contained_types();
	bool has_subtype() const;
	
	const symbol_qualities& get_qualities() const;
	symbol_qualities& get_qualities();

	size_t get_array_length() const;
	std::string get_struct_name() const;

	const expression::expression_base* get_array_length_expression() const;

	void set_primary(enumerations::primitive_type new_primary);
	void set_subtype(data_type new_subtype);
	void set_contained_types(std::vector<data_type> types_list);

	void set_array_length(size_t new_length);

	void add_qualities(symbol_qualities to_add);
    void add_quality(enumerations::symbol_quality to_add);

	void set_struct_name(std::string name);

	bool is_compatible(data_type to_compare) const;

	size_t get_width() const;

	bool is_reference_type() const;

	virtual bool must_initialize() const;
    bool must_free() const;

	/**
	 * Generates the decoration for the given type.
	 * 
	 * For example, `int` will generate `i`, but `final tuple<int, int, float &long>`
	 * would generate `tf:3i&i&fl`.
	 */
	std::string decorate() const;

    data_type(	enumerations::primitive_type primary, 
				data_type subtype, 
				symbol_qualities qualities, 
				std::shared_ptr<expression::expression_base> array_length_exp = nullptr, 
				const std::string& struct_name = ""	);
	data_type (	enumerations::primitive_type primary, 
				const std::vector<data_type>& contained_types, 
				symbol_qualities qualities	);
	data_type(enumerations::primitive_type primary);
	data_type(const data_type &ref);
	data_type();
	~data_type();
};
