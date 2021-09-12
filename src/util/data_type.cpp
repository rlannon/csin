#include "data_type.hpp"

#include <sstream>

const std::vector<
    std::pair<
        const enumerations::primitive_type,
        const std::string
    >
> data_type::_type_strings {
    std::make_pair<>(enumerations::primitive_type::INT, "i"),
    std::make_pair<>(enumerations::primitive_type::FLOAT, "f"),
    std::make_pair<>(enumerations::primitive_type::ARRAY, "a"),
    std::make_pair<>(enumerations::primitive_type::BOOL, "b"),
    std::make_pair<>(enumerations::primitive_type::CHAR, "c"),
    std::make_pair<>(enumerations::primitive_type::PTR, "p"),
    std::make_pair<>(enumerations::primitive_type::REFERENCE, "r"),
    std::make_pair<>(enumerations::primitive_type::STRING, "s"),
    std::make_pair<>(enumerations::primitive_type::STRUCT, "u"),
    std::make_pair<>(enumerations::primitive_type::TUPLE, "t"),
    std::make_pair<>(enumerations::primitive_type::VOID, "v")
};

void data_type::set_width()
{
	// All other types have different widths
	if (this->primary == enumerations::primitive_type::INT) {
		// ints are usually 4 bytes wide (32-bit), but can be 2 bytes for a short or 8 for a long 

		if (this->qualities.is_long()) {
			this->width = sin_widths::LONG_WIDTH;
		} else if (this->qualities.is_short()) {
			this->width = sin_widths::SHORT_WIDTH;
		} else {
			this->width = sin_widths::INT_WIDTH;
		}
	} else if (this->primary == enumerations::primitive_type::FLOAT) {
		// floats can also use the long and short keywords -- a long float is the same as a double, a short float is the same as a half

		if (this->qualities.is_long()) {
			this->width = sin_widths::DOUBLE_WIDTH;
		} else if (this->qualities.is_short()) {
			this->width = sin_widths::HALF_WIDTH;	// line number information, for the time being, will be caught wherever this type is used
			error::half_precision_not_supported_warning(0);
		} else {
			this->width = sin_widths::FLOAT_WIDTH;
		}
	} else if (this->primary == enumerations::primitive_type::BOOL) {
		// bools are only a byte wide
		this->width = sin_widths::BOOL_WIDTH;
	} else if (this->primary == enumerations::primitive_type::PTR || this->primary == enumerations::primitive_type::REFERENCE) {
		// because we are compiling to x86_64, pointers and references should be 64-bit
		this->width = sin_widths::PTR_WIDTH;
	} else if (this->primary == enumerations::primitive_type::STRING) {
		// since strings are all implemented as pointers, they have widths of 8 bytes
		// (they always point to dynamic memory, but syntactically don't behave like pointers)
		this->width = sin_widths::PTR_WIDTH;
	} else if (this->primary == enumerations::primitive_type::CHAR) {
		// todo: determine whether it is ASCII or UTF-8
		this->width = sin_widths::CHAR_WIDTH;
	} else if (this->primary == enumerations::primitive_type::TUPLE) {
		// tuple widths are known at compile time -- it is the sum of the widths of each of their contained types
		// however, if they contain a struct or an array, we must defer the width evaluation until we have a struct table
		this->width = 0;
		auto it = this->contained_types.begin();
		bool defer_width = false;
		while (it != this->contained_types.end() && !defer_width) {
			if (it->get_width() == 0) {	// types with unknown lengths have a width of 0
				this->width = 0;
				defer_width = true;
			}
			else {
				this->width += it->get_width();
			}

			it++;
		}
	}
	else {
		/*

		Everything else should use 0:
			void	-	a void type is literally nothing
			array	-	do not have defined widths, it depends on the array and its subtype
			struct	-	require the compiler to look for the width in the struct table
			
		While it is possible to calculate the width of arrays and structs if all of that information is known at compile time, it is possible that a struct member would only be known to the compiler through the "decl" keyword, in which case it would be impossible to know the width when the allocation was occurring.

		*/

		this->width = 0;
	}
}

void data_type::set_must_free() {
    if (
        (
            this->primary == enumerations::primitive_type::PTR &&
            this->qualities.is_managed()
        ) ||
        this->is_reference_type()
    ) {
        this->_must_free = true;
    }
    else if (this->primary == enumerations::primitive_type::ARRAY) {
        if (
            (
                this->get_subtype().primary == enumerations::primitive_type::PTR &&
                this->get_subtype().qualities.is_managed()
            ) ||
            this->get_subtype().is_reference_type()
        ) {
            this->_must_free = true;
        }
    }
    else if (this->primary == enumerations::primitive_type::TUPLE) {
        bool _free_contained = false;
        auto it = this->contained_types.begin();
        while (it != this->contained_types.end() && !_free_contained) {
            if (
                (it->primary == enumerations::primitive_type::PTR && it->qualities.is_managed()) || it->is_reference_type())
                _free_contained = true;
            else {
                it++;
            }
        }
        this->_must_free = _free_contained;
    }
    else {
        this->_must_free = false;
    }
    
    return;
}

/*

We can use the overloaded operators to do any of the following:
	- See if two data_type objects are equal
	- See if data_type is equal to {enumerations::primitive_type, enumerations::primitive_type}
	- See if data_type is equal to enumerations::primitive_type

*/

data_type& data_type::operator=(const data_type &right)
{
	// Copy assignment operator
	if (this != &right) {
		this->primary = right.primary;
		this->contained_types = right.contained_types;
		this->qualities = right.qualities;
		this->array_length = right.array_length;
		this->struct_name = right.struct_name;
		this->width = right.width;
		this->array_length_expression = right.array_length_expression;
	}
    this->set_must_free();

	return *this;
}

bool data_type::operator==(const data_type& right) const
{
	bool primary_match = this->primary == right.primary;
	bool subtype_match = true;
	if (!this->contained_types.empty() && !right.contained_types.empty()) {
		subtype_match = this->contained_types == right.contained_types;
	}
	else
		subtype_match = this->contained_types == right.contained_types;
	bool qualities_match = this->qualities == right.qualities;

	return primary_match && subtype_match && qualities_match;
}

bool data_type::operator!=(const data_type& right) const
{
	return !this->operator==(right);
}

bool data_type::operator==(const enumerations::primitive_type right) const
{
	return this->primary == right;
}

bool data_type::operator!=(const enumerations::primitive_type right) const
{
	return this->primary != right;
}

const bool data_type::is_valid_type_promotion(const symbol_qualities& left, const symbol_qualities& right) {
	if (left.is_const()) {
		return true;	// a const left-hand side will always promote the right-hand expression
	}
	else if (left.is_final()) {
		return !right.is_const();	// a const right-hand argument cannot be demoted
	}
	else {
		return !(right.is_const() || right.is_final());	// the right-hand argument cannot be demoted
	}
}

bool data_type::is_compatible(data_type to_compare) const
{
	bool compatible = false;

	if (this->primary == enumerations::primitive_type::RAW || to_compare.get_primary() == enumerations::primitive_type::RAW) {
		compatible = true;
	}
	else if (this->primary == enumerations::primitive_type::PTR && to_compare.get_primary() == enumerations::primitive_type::PTR) {
		// call is_compatible on the subtypes and ensure the type promotion is legal
		if (!this->contained_types.empty() && !to_compare.contained_types.empty()) {
			compatible = this->get_subtype().is_compatible(
				to_compare.get_subtype()
			) && is_valid_type_promotion(this->get_subtype().qualities, to_compare.get_subtype().qualities);
		} else {
			throw error::compiler_exception("Expected subtype", 0, 0);	// todo: ptr and array should _always_ have subtypes
		}
	}
	else if (this->primary == enumerations::primitive_type::REFERENCE) {
		// if we have a reference type, compare the reference subtype to to_compare
        compatible = this->get_subtype().is_compatible(to_compare);
	}
    else if (to_compare.get_primary() == enumerations::primitive_type::REFERENCE) {
        compatible = this->is_compatible(to_compare.get_subtype());
    }
	else if (this->primary == enumerations::primitive_type::ARRAY && to_compare.get_primary() == enumerations::primitive_type::ARRAY) {
		if (!this->contained_types.empty()) {
			compatible = this->get_subtype().is_compatible(
				to_compare.get_subtype()
			);
		}
		else {
			throw error::compiler_exception("Expected subtype", 0, 0);
		}
	}
	else if (this->primary == enumerations::primitive_type::TUPLE && to_compare.get_primary() == enumerations::primitive_type::TUPLE) {
		// tuples must have the same number of elements, and in the same order, to be compatible
		if (this->contained_types.size() == to_compare.contained_types.size()) {
			compatible = true;
			auto this_it = this->contained_types.begin();
			auto comp_it = to_compare.contained_types.begin();
			while (compatible && (this_it != this->contained_types.end()) && (comp_it != to_compare.contained_types.end())) {
				if (this_it->is_compatible(*comp_it)) {
					this_it++;
					comp_it++;
				}
				else {
					compatible = false;
				}
			}
		}
	}
	else {
		// primary types must be equal
		// todo: generate warnings for width and sign differences
		compatible = (
			(this->primary == to_compare.primary) || 
			(this->primary == enumerations::primitive_type::STRING && to_compare.primary == enumerations::primitive_type::CHAR)
		);
	}

	return compatible;
}

enumerations::primitive_type data_type::get_primary() const
{
	return this->primary;
}

const symbol_qualities& data_type::get_qualities() const {
	return this->qualities;
}

symbol_qualities& data_type::get_qualities() {
	return this->qualities;
}

size_t data_type::get_array_length() const {
	return this->array_length;
}

std::string data_type::get_struct_name() const {
	return this->struct_name;
}

const expression::expression_base* data_type::get_array_length_expression() const {
	return this->array_length_expression.get();
}

data_type data_type::get_subtype() const {
	data_type to_return(enumerations::primitive_type::NONE);
	
	if (!this->contained_types.empty()) {
		to_return = this->contained_types[0];
	}

	return to_return;
}

const std::vector<data_type>& data_type::get_contained_types() const {
	return this->contained_types;
}

std::vector<data_type>& data_type::get_contained_types() {
	return this->contained_types;
}

bool data_type::has_subtype() const {
	return !this->contained_types.empty();
}

void data_type::set_primary(enumerations::primitive_type new_primary) {
	this->primary = new_primary;
}

void data_type::set_subtype(data_type new_subtype) {
	if (!this->contained_types.empty()) {
		this->contained_types[0] = new_subtype;
	}
	else {
		this->contained_types.push_back(new_subtype);
	}
}

void data_type::set_contained_types(std::vector<data_type> types_list) {
	this->contained_types = types_list;
}

void data_type::set_array_length(size_t new_length) {
	this->array_length = new_length;
}

void data_type::add_qualities(symbol_qualities to_add) {
	// simply use the "SymbolQualities::add_qualities" function
	this->qualities.add_qualities(to_add);

    // update the width
    this->set_width();
}

void data_type::add_quality(enumerations::symbol_quality to_add) {
    // add a quality 'to_add' to the data type
    this->qualities.add_quality(to_add);

	// generate a compiler warning if the primary type doesn't support the quality (has no effect)
	if (this->primary == enumerations::primitive_type::PTR || 
		this->primary == enumerations::primitive_type::BOOL || 
		this->primary == enumerations::primitive_type::ARRAY || 
		this->primary == enumerations::primitive_type::STRING || 
		this->primary == enumerations::primitive_type::RAW) 
	{
		if (to_add == enumerations::symbol_quality::LONG || 
			to_add == enumerations::symbol_quality::SHORT || 
			to_add == enumerations::symbol_quality::SIGNED ||
			to_add == enumerations::symbol_quality::UNSIGNED) 
		{
			error::compiler_note("Width and sign qualifiers have no effect for this type; as such, this quality will be ignored");
		}
	}

    // update the width
    this->set_width();
}

void data_type::set_struct_name(std::string name) {
	// Sets the name of the struct
	this->struct_name = name;
}

size_t data_type::get_width() const {
	return this->width;
}

bool data_type::is_valid_type(const data_type &t) {
	bool is_valid = true;

	if (t.primary == enumerations::primitive_type::FLOAT) {
		// half-precision or short floats are not supported
		if (t.qualities.is_short()) {
			is_valid = false;
		}
	}
	else if (t.primary == enumerations::primitive_type::STRING) {
		// strings are not numerics and so may not be used with signed or unsigned qualifiers
		if (t.qualities.has_sign_quality()) {
			is_valid = false;
		}

		// they may also not use 'static' unless they are 'static const'; they are inherently dynamic
		if (t.qualities.is_static() && !t.get_qualities().is_const()) {
			is_valid = false;
		}
	}
	else if (t.primary == enumerations::primitive_type::STRUCT) {
		// structs don't support numeric or width qualifiers
		if (t.qualities.is_long() || t.qualities.is_short() || t.qualities.has_sign_quality()) {
			is_valid = false;
		}
	}
	else if (t.primary == enumerations::primitive_type::REFERENCE)
	{
		return t.qualities.is_managed();
	}

	return is_valid;
}

bool data_type::is_reference_type() const {
	return	this->get_qualities().is_dynamic() || 
			this->primary == enumerations::primitive_type::STRING ||
			this->primary == enumerations::primitive_type::REFERENCE;
}

bool data_type::must_initialize() const {
	/*

	must_initialize
	Determines whether the type must be initialized in its allocation

	Check the documentation (specifically, docs/Construction.md) for the exact rules

	*/

	bool init_required = false;
	init_required = this->get_qualities().is_const();
	init_required = init_required || this->get_primary() == enumerations::primitive_type::REFERENCE;
	if (this->get_primary() == enumerations::primitive_type::ARRAY) {

	}
	
	// todo: how to handle tuples?
	return init_required;
}

bool data_type::must_free() const {
    return this->_must_free;
}

std::string data_type::decorate() const
{
	std::stringstream decorated;

	auto it = _type_strings.find(primary);
	if (it == _type_strings.end())
	{
		throw error::type_error(0);
	}

	decorated << it->second;
	if (primary == enumerations::primitive_type::STRUCT)
	{
		decorated << "?" << struct_name << "?";
	}

	decorated << qualities.decorate();

	if (primary == enumerations::primitive_type::ARRAY)
	{
		decorated << ":" << array_length;
	}
	else if (primary == enumerations::primitive_type::TUPLE)
	{
		decorated << ":" << contained_types.size();
	}

	bool first = true;
	for (const auto& contained: contained_types)
	{
		if (first)
		{
			decorated << "&";
			first = false;
		}

		decorated << contained.decorate();
	}

	return decorated.str();
}

data_type::data_type
(
    enumerations::primitive_type primary,
    data_type subtype,
    symbol_qualities qualities,
    std::shared_ptr<expression::expression_base> array_length_exp,
    const std::string& struct_name
):
    primary(primary),
    qualities(qualities),
	array_length_expression(array_length_exp),
	struct_name(struct_name)
{
	// create the vector with our subtype
	// if we have a string type, set the subtype to enumerations::primitive_type::CHAR
	if (primary == enumerations::primitive_type::STRING) {
		subtype = data_type(enumerations::primitive_type::CHAR);
	}

	this->contained_types.push_back(subtype);

	// the array length will be evaluated by the compiler; start at 0
	this->array_length = 0;
	
    // if the type is int, set signed to true if it is not unsigned
	if (primary == enumerations::primitive_type::INT && !this->qualities.is_unsigned()) {
		this->qualities.add_quality(enumerations::symbol_quality::SIGNED);
	}
	else if (primary == enumerations::primitive_type::FLOAT)
	{
		this->qualities.add_quality(enumerations::symbol_quality::SIGNED);
	}

	// set the data width
	this->set_width();
    this->set_must_free();
}

data_type::data_type(enumerations::primitive_type primary, const std::vector<data_type>& contained_types, symbol_qualities qualities):
	primary(primary),
	contained_types(contained_types),
	qualities(qualities)
{
	// update the rest of our members
	this->array_length = 0;
	this->struct_name = "";
	this->set_width();
    this->set_must_free();
}

data_type::data_type(enumerations::primitive_type primary) 
	: data_type(
		primary,
		data_type(),
		symbol_qualities(),
		nullptr,
		"") 
	{ }

data_type::data_type(const data_type &ref)
	: primary(ref.primary)
	, contained_types(ref.contained_types)
	, qualities(ref.qualities)
	, array_length(ref.array_length)
	, array_length_expression(ref.array_length_expression)
	, struct_name(ref.struct_name)
	, width(ref.width)
{
	this->set_must_free();
}

data_type::data_type()
{
	this->primary = enumerations::primitive_type::NONE;
	this->qualities = symbol_qualities();	// no qualities to start
	this->array_length = 0;
	this->width = 0;
	this->struct_name = "";
	this->array_length_expression = nullptr;
    this->_must_free = false;
}

data_type::~data_type() {}
