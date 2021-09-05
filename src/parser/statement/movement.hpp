#pragma once

#include "assignment.hpp"

namespace statement
{
    class movement : public assignment
    {
    public:
        movement(std::unique_ptr<expression::expression_base>&& lvalue, std::unique_ptr<expression::expression_base>&& rvalue);
        virtual ~movement() = default;
    };
}
