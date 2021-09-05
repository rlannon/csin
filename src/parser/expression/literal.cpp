#include "literal.hpp"

namespace expression
{
    void literal::set_type(data_type t) {
        this->type = t;
    }

    const data_type& literal::get_data_type() const {
        return this->type;
    }

    const std::string& literal::get_value() const {
        return this->value;
    }

    void literal::override_qualities(symbol_qualities sq) {
        // update the data type (for postfixed quality overrides)
        this->type.add_qualities(sq);	// todo: ensure the type override is valid
    }

    bool literal::has_type_information() const {
        return true;
    }

    literal::literal(   enumerations::primitive_type primitive_type,
                        const std::string& value, 
                        enumerations::primitive_type subtype)
        : expression_base(enumerations::expression_type::LITERAL)
        , value(value) 
        {
            // symbol qualities for our data_type object
            bool const_q = true;
            bool long_q = false;
            bool short_q = false;
            bool signed_q = true;

            // set our symbol qualities
            symbol_qualities qualities(const_q, false, false, signed_q, !signed_q, long_q, short_q);  // literals are always considered const
            this->type = data_type(primitive_type, subtype, qualities);
        }

    literal::literal(const data_type& t, const std::string& value): expression_base(enumerations::expression_type::LITERAL) {
        this->type = t;
        this->value = value;
    }

    literal::literal(): expression_base(enumerations::expression_type::LITERAL) {
        this->type = data_type();
    }
}
