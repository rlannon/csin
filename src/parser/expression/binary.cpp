#include "binary.hpp"

namespace expression
{
    std::unique_ptr<expression_base> binary::get_left_unique()
    {
        return std::move(this->left_exp);
    }

    std::unique_ptr<expression_base> binary::get_right_unique()
    {
        return std::move(this->right_exp);
    }

    const expression_base &binary::get_left() const {
        return *this->left_exp.get();
    }

    const expression_base &binary::get_right() const {
        return *this->right_exp.get();
    }

    enumerations::exp_operator binary::get_operator() const {
        return this->op;
    }

    binary::binary( std::unique_ptr<expression_base> left_exp,
                    std::unique_ptr<expression_base> right_exp,
                    const enumerations::exp_operator op)
        : expression_base(enumerations::expression_type::BINARY)
        , left_exp(std::move(left_exp))
        , right_exp(std::move(right_exp))
        , op(op) { }

    binary::binary()
        : expression_base(enumerations::expression_type::BINARY)
        , op(enumerations::exp_operator::NO_OP) { }
}
