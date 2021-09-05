#include "identifier.hpp"

namespace expression
{
    const std::string& identifier::getValue() const {
        return this->value;
    }

    void identifier::setValue(const std::string& new_value) {
        this->value = new_value;
    }

    identifier::identifier(const std::string& value)
        : expression_base(enumerations::expression_type::IDENTIFIER)
        , value(value) { }

    identifier::identifier()
        : identifier("") { }
}
