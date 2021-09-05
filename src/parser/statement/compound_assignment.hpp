#pragma once

#include "assignment.hpp"

namespace statement
{
    class compound_assignment : public assignment
    {
        enumerations::exp_operator _op;
    public:
        enumerations::exp_operator get_operator() const;

        compound_assignment(std::unique_ptr<expression::expression_base>&& lvalue, 
                            std::unique_ptr<expression::expression_base> && rvalue, 
                            enumerations::exp_operator op);
        compound_assignment();
        virtual ~compound_assignment() = default;
    };
}
