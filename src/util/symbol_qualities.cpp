#include "symbol_qualities.hpp"

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
		(this->long_q == right.long_q) &&
		(this->short_q == right.short_q) &&
		(this->signed_q == right.signed_q) &&
		(this->const_q == right.const_q) &&
		(this->final_q == right.final_q) &&
		(this->dynamic_q == right.dynamic_q) &&
		(this->extern_q == right.extern_q) &&
		(this->c64_con == right.c64_con) &&
		(this->windows_con == right.windows_con) &&
		(this->sincall_con == right.sincall_con) &&
        (this->_managed == right._managed)
	);
}

bool symbol_qualities::operator!=(const symbol_qualities& right) const {
	return !this->operator==(right);
}

bool symbol_qualities::is_long() const
{
    return long_q;
}

bool symbol_qualities::is_short() const
{
    return short_q;
}

bool symbol_qualities::is_const() const
{
	return const_q;
}

bool symbol_qualities::is_final() const
{
	return final_q;
}

bool symbol_qualities::is_dynamic() const
{
	return dynamic_q;
}

bool symbol_qualities::is_static() const
{
	return static_q;
}

bool symbol_qualities::is_signed() const
{
	return signed_q;
}

bool symbol_qualities::is_unsigned() const
{
	return !signed_q;
}

bool symbol_qualities::has_sign_quality() const
{
    return signed_q || _listed_unsigned;
}

bool symbol_qualities::is_extern() const
{
	return extern_q;
}

bool symbol_qualities::is_managed() const
{
    return _managed;
}

void symbol_qualities::add_qualities(symbol_qualities to_add) {
	// combines two SymbolQualities objects

	// todo: refactor how qualities are stored in SymbolQualities so that we can simplify this
	// todo: quality conflict exceptions

	if (to_add.const_q) this->add_quality(enumerations::symbol_quality::CONSTANT);
	if (to_add.final_q) this->add_quality(enumerations::symbol_quality::FINAL);
	if (to_add.static_q) this->add_quality(enumerations::symbol_quality::STATIC);
	if (to_add.dynamic_q) this->add_quality(enumerations::symbol_quality::DYNAMIC);
	if (to_add.long_q) this->add_quality(enumerations::symbol_quality::LONG);
	if (to_add.short_q) this->add_quality(enumerations::symbol_quality::SHORT);
	if (to_add.signed_q) this->add_quality(enumerations::symbol_quality::SIGNED);
	if (to_add.is_unsigned()) this->add_quality(enumerations::symbol_quality::UNSIGNED);
	if (to_add.extern_q) this->add_quality(enumerations::symbol_quality::EXTERN);
    if (!to_add._managed) this->add_quality(enumerations::symbol_quality::UNMANAGED);
}

void symbol_qualities::add_quality(enumerations::symbol_quality to_add)
{
    // Add a single quality to our qualities list
    if (to_add == enumerations::symbol_quality::CONSTANT) {
        const_q = true;

		// we cannot have final and const together
		if (final_q) throw std::string("const");	// todo: proper exception type
    } else if (to_add == enumerations::symbol_quality::FINAL) {
		final_q = true;

		// we cannot have final and const together
		if (const_q) throw std::string("final");	// todo: proper exception type
	} else if (to_add == enumerations::symbol_quality::STATIC) {
        static_q = true;
    } else if (to_add == enumerations::symbol_quality::DYNAMIC) {
        dynamic_q = true;
    } else if (to_add == enumerations::symbol_quality::SIGNED) {
        signed_q = true;
    } else if (to_add == enumerations::symbol_quality::UNSIGNED) {
        signed_q = false;
	}
	else if (to_add == enumerations::symbol_quality::LONG) {
		long_q = true;
		short_q = false;
	}
	else if (to_add == enumerations::symbol_quality::SHORT) {
		long_q = false;
		short_q = true;
	}
	else if (to_add == enumerations::symbol_quality::EXTERN) {
		extern_q = true;
	}
    else if (to_add == enumerations::symbol_quality::UNMANAGED) {
        _managed = false;
    }
	else {
		// invalid quality; throw an exception
		throw error::compiler_exception("Quality conflict");	// todo: proper exception type
	}
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
			const_q = true;
		}
		else if (*it == enumerations::symbol_quality::FINAL)
		{
			final_q = true;
		}
		else if (*it == enumerations::symbol_quality::STATIC)
		{
			static_q = true;
		}
		else if (*it == enumerations::symbol_quality::DYNAMIC)
		{
			dynamic_q = true;
		}
		else if (*it == enumerations::symbol_quality::SIGNED)
		{
			signed_q = true;
		}
		else if (*it == enumerations::symbol_quality::UNSIGNED)
		{
			signed_q = false;
            _listed_unsigned = true;
		}
		else if (*it == enumerations::symbol_quality::EXTERN) {
			extern_q = true;
		}
        else if (*it == enumerations::symbol_quality::UNMANAGED) {
            _managed = false;
        }
		else {
			continue;
		}
	}
}

symbol_qualities::symbol_qualities(bool is_const, bool is_static, bool is_dynamic, bool is_signed, bool is_long, bool is_short, bool is_extern) :
	const_q(is_const),
	static_q(is_static),
	dynamic_q(is_dynamic),
	signed_q(is_signed),
	long_q(is_long),
	short_q(is_short),
	extern_q(is_extern)
{
	// const will always win out over dynamic (can be 'static const')
	if (this->const_q) {
		this->dynamic_q = false;
	}
	this->final_q = false;

	// if both long and short are set, generate a warning
	if (this->long_q && this->short_q) {
		// todo: warning
		std::cerr << "Warning: 'long' and 'short' both used as qualifiers; this amounts to a regular integer" << std::endl;

		// delete both qualities
		this->long_q = false;
		this->short_q = false;
	}

    this->_managed = true;
}

symbol_qualities::symbol_qualities()
{
	const_q = false;
	final_q = false;
	static_q = false;
	dynamic_q = false;
	signed_q = false;
	long_q = false;
	short_q = false;
	extern_q = false;

    _listed_unsigned = false;
    _managed = true;
}

symbol_qualities::~symbol_qualities()
{

}
