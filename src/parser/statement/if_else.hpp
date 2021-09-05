#pragma once

#include "statement.hpp"
#include "../expression/expression.hpp"

namespace statement
{
    class if_else : public statement_base
    {
        std::unique_ptr<expression::expression_base> condition;
        std::unique_ptr<statement_base> if_branch;	// branches may be single statements or scope blocks
        std::unique_ptr<statement_base> else_branch;
    public:
        const expression::expression_base& get_condition() const;
        const statement_base* get_if_branch() const;
        const statement_base* get_else_branch() const;

        if_else(std::unique_ptr<expression::expression_base>&& condition, 
                std::unique_ptr<statement_base>&& if_branch,
                std::unique_ptr<statement_base>&& else_branch);
        if_else(std::unique_ptr<expression::expression_base>&& condition, 
                std::unique_ptr<statement_base>&& if_branch);
        if_else();
        virtual ~if_else() = default;
    };
}
