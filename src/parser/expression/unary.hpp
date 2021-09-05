#pragma once

#include "expression.hpp"
#include "../../util/enumerated_types.hpp"

namespace expression
{
    class unary : public expression_base
    {
        enumerations::exp_operator op;
        std::unique_ptr<expression_base> operand;
    public:
        enumerations::exp_operator get_operator() const;
        const expression_base &get_operand() const;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<unary>(operand->clone(), op);
        }

        unary(std::unique_ptr<expression_base> operand, enumerations::exp_operator op);
        unary();
        virtual ~unary() override;
    };
}
