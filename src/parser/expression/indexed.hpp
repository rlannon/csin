#pragma once

#include "expression.hpp"

namespace expression
{
    class indexed : public expression_base
    {
        std::unique_ptr<expression_base> index_value;	// the index value is simply an expression
        std::unique_ptr<expression_base> to_index;	// what we are indexing
    public:
        const expression_base &get_index_value() const;
        const expression_base &get_to_index() const;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<indexed>(
                to_index->clone(),
                index_value->clone()
            );
        }

        indexed(std::unique_ptr<expression_base> to_index, std::unique_ptr<expression_base> index_value);
        indexed();
    };
}
