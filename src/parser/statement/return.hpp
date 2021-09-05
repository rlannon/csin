#pragma once

#include "statement.hpp"
#include "../expression/expression.hpp"

namespace statement
{
    class return_statement : public statement_base
    {
        std::unique_ptr<expression::expression_base> return_exp;
    public:
        const expression::expression_base& get_return_exp() const;

        return_statement(std::unique_ptr<expression::expression_base>&& exp_ptr);
        return_statement();
        virtual ~return_statement() = default;
    };
}
