#pragma once

#include "expression.hpp"
#include "../../util/enumerated_types.hpp"

namespace expression
{
    class attribute_selection;
    class typecast;
    
    class binary : public expression_base
    {
        friend class attribute_selection;
        friend class typecast;

        enumerations::exp_operator op;	// +, -, etc.
        std::unique_ptr<expression_base> left_exp;
        std::unique_ptr<expression_base> right_exp;

        std::unique_ptr<expression_base> get_left_unique();
        std::unique_ptr<expression_base> get_right_unique();
    public:
        const expression_base &get_left() const;
        const expression_base &get_right() const;

        enumerations::exp_operator get_operator() const;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<binary>(
                left_exp->clone(),
                right_exp->clone(),
                op
            );
        }

        binary( std::unique_ptr<expression_base> left, 
                std::unique_ptr<expression_base> right, 
                const enumerations::exp_operator op);
        binary();

        virtual ~binary() override;
    };
}
