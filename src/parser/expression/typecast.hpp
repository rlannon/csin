#pragma once

#include "expression.hpp"
#include "binary.hpp"
#include "../../util/data_type.hpp"

namespace expression
{
    class typecast : public expression_base
    {
        std::unique_ptr<expression_base> to_cast;	// any expression can be casted
        data_type new_type;	// the new type for the expression
    public:
        const expression_base &get_exp() const;
        const data_type &get_new_type() const;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<typecast>(to_cast->clone(), new_type);
        }

        typecast(typecast &old);
        typecast(std::unique_ptr<expression_base> to_cast, const data_type& new_type);
        typecast(std::unique_ptr<binary> b);

        virtual ~typecast() override;
    };
}
