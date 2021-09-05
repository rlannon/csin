#include "expression.hpp"

namespace expression
{
    bool expression_base::is_const() const
    {
        return this->_const;
    }

    enumerations::expression_type expression_base::get_expression_type() const
    {
        return this->_expression_type;
    }

    void expression_base::set_const()
    {
        // marks an expression as a constexpr
        this->_const = true;
    }

    void expression_base::override_qualities(symbol_qualities sq) {
        // base class override symbol qualities
        // todo: datatype for base?
    }

    bool expression_base::has_type_information() const {
        return false;
    }

    bool expression_base::was_overridden() const {
        return this->_overridden;
    }

    expression_base::expression_base(const enumerations::expression_type expression_type)
        : _expression_type(expression_type)
        , _const(false)
        , _overridden(false) {}

    expression_base::expression_base()
        : expression_base(enumerations::expression_type::EXPRESSION_GENERAL) {}

    expression_base::~expression_base() {}
}
