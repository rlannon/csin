#pragma once

#include "expression.hpp"

namespace expression
{
    class list_expression : public expression_base
    {
        enumerations::primitive_type primary;
        std::vector<std::unique_ptr<expression_base>> list_members;
    public:
        std::vector<const expression_base*> get_list() const;
        bool has_type_information() const override;
        enumerations::primitive_type get_list_type() const;	// the list type that we parsed -- () yields TUPLE, {} yields ARRAY

        void add_item(std::unique_ptr<expression_base> to_add, const size_t index);

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            auto le = std::make_unique<list_expression>();
            le->primary = primary;
            for (auto it = list_members.begin(); it != list_members.end(); it++)
            {
                le->list_members.push_back(it->get()->clone());
            }
            return le;
        }

        list_expression(std::vector<std::unique_ptr<expression_base>>& list_members, enumerations::primitive_type list_type);
        list_expression(std::unique_ptr<expression_base> arg, enumerations::primitive_type list_type);
        list_expression();
        virtual ~list_expression() = default;
    };   
}
