#pragma once

#include "expression.hpp"
#include "../../util/data_type.hpp"
#include "../../util/symbol_qualities.hpp"

#include <string>
#include <memory>

namespace expression
{
    class literal : public expression_base
    {
        data_type type;
        std::string value;
    public:
        void set_type(data_type t);
        const data_type& get_data_type() const;
        const std::string& get_value() const;

        void override_qualities(symbol_qualities sq) override;
        bool has_type_information() const override;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<literal>(type, value);
        }

        literal(enumerations::primitive_type primitive_type, 
                const std::string& value, 
                enumerations::primitive_type subtype = enumerations::primitive_type::NONE);
        literal(const data_type& t, const std::string& value);
        literal();
        virtual ~literal() override;
    };
}
