#pragma once

#include "statement.hpp"
#include "../expression/identifier.hpp"

namespace statement
{
    class assignment : public statement_base
    {
    protected:
        std::unique_ptr<expression::expression_base> lvalue;
        std::unique_ptr<expression::expression_base> rvalue_ptr;
    public:
        const expression::expression_base& get_lvalue() const;
        const expression::expression_base& get_rvalue() const;

        assignment(std::unique_ptr<expression::expression_base>&& lvalue, std::unique_ptr<expression::expression_base>&& rvalue);
        assignment(const expression::identifier& lvalue, std::unique_ptr<expression::expression_base>&& rvalue);
        assignment();
        virtual ~assignment() = default;
    };
}
