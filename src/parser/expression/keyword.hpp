#pragma once

#include "expression.hpp"
#include "../../util/data_type.hpp"
#include "../../util/symbol_qualities.hpp"

#include <string>

namespace expression
{
    class keyword: public expression_base
    {
        data_type _type;
        std::string _keyword;
    public:
        bool has_type_information() const override;
        void override_qualities(symbol_qualities sq) override;

        const std::string& get_keyword() const;
        const data_type &get_type() const;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            return std::make_unique<keyword>(_type, _keyword);
        }

        keyword(const std::string& kwd);
        keyword(const data_type& t);
        keyword(const data_type& t, const std::string& kwd);
    };
}
