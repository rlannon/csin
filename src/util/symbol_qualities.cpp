#include "symbol_qualities.hpp"

#include <sstream>

const std::unordered_map<std::string, enumerations::symbol_quality> symbol_qualities::quality_strings = {
	{ "const", enumerations::symbol_quality::CONSTANT },
	{ "final", enumerations::symbol_quality::FINAL },
	{ "static", enumerations::symbol_quality::STATIC },
	{ "dynamic", enumerations::symbol_quality::DYNAMIC },
	{ "long", enumerations::symbol_quality::LONG },
	{ "short", enumerations::symbol_quality::SHORT },
	{ "signed", enumerations::symbol_quality::SIGNED },
	{ "unsigned", enumerations::symbol_quality::UNSIGNED },
	{ "extern", enumerations::symbol_quality::EXTERN },
    { "unmanaged", enumerations::symbol_quality::UNMANAGED }
};

bool symbol_qualities::operator==(const symbol_qualities& right) const {
	return (
		(this->_qualities[_long_index] == right._qualities[_long_index]) &&
		(this->_qualities[_short_index] == right._qualities[_short_index]) &&
		(this->_qualities[_signed_index] == right._qualities[_signed_index]) &&
		(this->_qualities[_const_index] == right._qualities[_const_index]) &&
		(this->_qualities[_final_index] == right._qualities[_final_index]) &&
		(this->_qualities[_dynamic_index] == right._qualities[_dynamic_index]) &&
		(this->_qualities[_extern_index] == right._qualities[_extern_index]) &&
		(this->_qualities[_managed_index] == right._qualities[_managed_index])
	);
}

bool symbol_qualities::operator!=(const symbol_qualities& right) const {
	return !this->operator==(right);
}

bool symbol_qualities::is_long() const
{
    return _qualities[_long_index];
}

bool symbol_qualities::is_short() const
{
    return _qualities[_short_index];
}

bool symbol_qualities::is_const() const
{
	return _qualities[_const_index];
}

bool symbol_qualities::is_final() const
{
	return _qualities[_final_index];
}

bool symbol_qualities::is_dynamic() const
{
	return _qualities[_dynamic_index];
}

bool symbol_qualities::is_static() const
{
	return _qualities[_static_index];
}

bool symbol_qualities::is_signed() const
{
	return _qualities[_signed_index];
}

bool symbol_qualities::is_unsigned() const
{
	return !_qualities[_signed_index];
}

bool symbol_qualities::has_sign_quality() const
{
    return _qualities[_signed_index] || _qualities[_listed_unsigned_index];
}

bool symbol_qualities::is_extern() const
{
	return _qualities[_extern_index];
}

bool symbol_qualities::is_managed() const
{
    return _qualities[_managed_index];
}

void symbol_qualities::add_qualities(symbol_qualities to_add)
{
	if (to_add._qualities[_const_index])
		this->add_quality(enumerations::symbol_quality::CONSTANT);
	
	if (to_add._qualities[_final_index])
		this->add_quality(enumerations::symbol_quality::FINAL);
	
	if (to_add._qualities[_static_index])
		this->add_quality(enumerations::symbol_quality::STATIC);
	
	if (to_add._qualities[_dynamic_index])
		this->add_quality(enumerations::symbol_quality::DYNAMIC);
	
	if (to_add._qualities[_long_index])
		this->add_quality(enumerations::symbol_quality::LONG);
	
	if (to_add._qualities[_short_index])
		this->add_quality(enumerations::symbol_quality::SHORT);
	
	if (to_add._qualities[_signed_index])
		this->add_quality(enumerations::symbol_quality::SIGNED);
	
	if (to_add.is_unsigned())
		this->add_quality(enumerations::symbol_quality::UNSIGNED);
	
	if (to_add._qualities[_extern_index])
		this->add_quality(enumerations::symbol_quality::EXTERN);
    
	if (!to_add._qualities[_managed_index])
		this->add_quality(enumerations::symbol_quality::UNMANAGED);
}

void symbol_qualities::add_quality(enumerations::symbol_quality to_add)
{
    // Add a single quality to our qualities list
    if (to_add == enumerations::symbol_quality::CONSTANT) {
        _qualities[_const_index] = true;
		if (_qualities[_final_index]) 
			throw error::quality_conflict("final", 0);
    }
	else if (to_add == enumerations::symbol_quality::FINAL) {
		_qualities[_final_index] = true;
		if (_qualities[_const_index]) throw error::quality_conflict("const", 0);
	} 
	else if (to_add == enumerations::symbol_quality::STATIC) {
        _qualities[_static_index] = true;
    }
	else if (to_add == enumerations::symbol_quality::DYNAMIC) {
        _qualities[_dynamic_index] = true;
    }
	else if (to_add == enumerations::symbol_quality::SIGNED) {
        _qualities[_signed_index] = true;
    }
	else if (to_add == enumerations::symbol_quality::UNSIGNED) {
        _qualities[_signed_index] = false;
		_qualities[_listed_unsigned_index] = true;
	}
	else if (to_add == enumerations::symbol_quality::LONG) {
		_qualities[_long_index] = true;
		_qualities[_short_index] = false;
	}
	else if (to_add == enumerations::symbol_quality::SHORT) {
		_qualities[_long_index] = false;
		_qualities[_short_index] = true;
	}
	else if (to_add == enumerations::symbol_quality::EXTERN) {
		_qualities[_extern_index] = true;
	}
    else if (to_add == enumerations::symbol_quality::UNMANAGED) {
        _qualities[_managed_index] = false;
    }
	else {
		throw error::illegal_quality("no quality", 0);
	}
}

std::string symbol_qualities::decorate() const
{
	std::stringstream decorated;

	for (size_t i = 0; i < _qualities.size(); i++)
	{
		if (_qualities[i])
			decorated << _decorations[i];
	}	

	return decorated.str();
}

symbol_qualities::symbol_qualities(std::vector<enumerations::symbol_quality> qualities):
    symbol_qualities()
{
	// todo: there must be a better way of doing this

	// then, populate according to the vector
	for (std::vector<enumerations::symbol_quality>::iterator it = qualities.begin(); it != qualities.end(); it++)
	{
		if (*it == enumerations::symbol_quality::CONSTANT)
		{
			_qualities[_const_index] = true;
		}
		else if (*it == enumerations::symbol_quality::FINAL)
		{
			_qualities[_final_index] = true;
		}
		else if (*it == enumerations::symbol_quality::STATIC)
		{
			_qualities[_static_index] = true;
		}
		else if (*it == enumerations::symbol_quality::DYNAMIC)
		{
			_qualities[_dynamic_index] = true;
		}
		else if (*it == enumerations::symbol_quality::SIGNED)
		{
			_qualities[_signed_index] = true;
		}
		else if (*it == enumerations::symbol_quality::UNSIGNED)
		{
			_qualities[_signed_index] = false;
            _qualities[_listed_unsigned_index] = true;
		}
		else if (*it == enumerations::symbol_quality::EXTERN) {
			_qualities[_extern_index] = true;
		}
        else if (*it == enumerations::symbol_quality::UNMANAGED) {
            _qualities[_managed_index] = false;
        }
		else {
			continue;
		}
	}
}

symbol_qualities::symbol_qualities(	bool is_const,
									bool is_static,
									bool is_dynamic,
									bool is_signed,
									bool is_long,
									bool is_short,
									bool is_extern	)
	: symbol_qualities()
{
	_qualities[_const_index] = is_const;
	_qualities[_static_index] = is_static;
	_qualities[_dynamic_index] = is_dynamic;
	_qualities[_signed_index] = is_signed;
	_qualities[_long_index] = is_long;
	_qualities[_short_index] = is_short;
	_qualities[_extern_index] = is_extern;

	// const will always win out over dynamic (can be 'static const')
	if (this->_qualities[_const_index]) {
		this->_qualities[_dynamic_index] = false;
	}
	this->_qualities[_final_index] = false;

	// if both long and short are set, generate a warning
	if (this->_qualities[_long_index] && this->_qualities[_short_index]) {
		// todo: warning
		std::cerr << "Warning: 'long' and 'short' both used as qualifiers; this amounts to a regular integer" << std::endl;

		// delete both qualities
		this->_qualities[_long_index] = false;
		this->_qualities[_short_index] = false;
	}

    this->_qualities[_managed_index] = true;
}

symbol_qualities::symbol_qualities(const symbol_qualities& other)
	: _qualities(other._qualities) {}

symbol_qualities::symbol_qualities()
{
	_qualities[_const_index] = false;
	_qualities[_final_index] = false;
	_qualities[_static_index] = false;
	_qualities[_dynamic_index] = false;
	_qualities[_signed_index] = false;
	_qualities[_long_index] = false;
	_qualities[_short_index] = false;
	_qualities[_extern_index] = false;
    _qualities[_listed_unsigned_index] = false;
    _qualities[_managed_index] = true;
}

symbol_qualities::~symbol_qualities() { }
