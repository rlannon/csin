#include "unary.hpp"

namespace expression
{
    enumerations::exp_operator unary::get_operator() const {
        return this->op;
    }

    const expression_base &unary::get_operand() const {
        return *this->operand.get();
    }

    unary::unary(std::unique_ptr<expression_base> operand, exp_operator op)
        : expression_base(enumerations::expression_type::UNARY)
        , operand(std::move(operand))
        , op(op) { }

    unary::unary(): expression_base(enumerations::expression_type::UNARY) {
        this->op = enumerations::exp_operator::NO_OP;
    }

    unary::~unary() {}
}
