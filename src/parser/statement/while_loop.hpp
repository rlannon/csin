#pragma once

#include "statement.hpp"
#include "../expression/expression.hpp"

namespace statement
{
    class while_loop : public statement_base
    {
        std::unique_ptr<expression::expression_base> condition;
        std::unique_ptr<statement_base> branch;
    public:
        const expression::expression_base& get_condition() const;
        const statement_base* get_branch() const;

        while_loop(std::unique_ptr<expression::expression_base>&& condition, std::unique_ptr<statement_base>&& branch);
        while_loop();
        virtual ~while_loop() = default;
    };
}
