#pragma once

#include "expression.hpp"

namespace expression
{
    class list_expression;

    class procedure: public expression_base
    {
        std::unique_ptr<expression_base> name;
        std::unique_ptr<expression_base> args;
    public:
        const expression_base &get_func_name() const;
        const list_expression &get_args() const;
        const expression_base &get_arg(size_t arg_no) const;
        size_t get_num_args() const;

        void insert_arg(std::unique_ptr<expression_base> to_insert, const size_t index);

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<procedure>(name->clone(), args->clone());
        }

        procedure(procedure& other);
        procedure(std::unique_ptr<expression_base> proc_name, std::unique_ptr<expression_base> proc_args);
        procedure();
        virtual ~procedure() = default;
    };
}
