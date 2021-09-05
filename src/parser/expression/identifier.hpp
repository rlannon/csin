#pragma once

#include "expression.hpp"

namespace expression
{
    class identifier : public expression_base
    {
    protected:
        std::string value;	// the name of the variable
    public:
        const std::string& getValue() const;
        void setValue(const std::string& new_value);

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<identifier>(value);
        }

        identifier(const std::string& value);
        identifier();
        virtual ~identifier() = default;
    };
}
