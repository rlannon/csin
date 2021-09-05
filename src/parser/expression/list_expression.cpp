#include "list_expression.hpp"

namespace expression
{
    bool list_expression::has_type_information() const {
        return true;
    }

    enumerations::primitive_type list_expression::get_list_type() const {
        return this->primary;
    }

    std::vector<const expression_base*> list_expression::get_list() const
    {
        std::vector<const expression_base*> to_return;
        for (auto it = this->list_members.begin(); it != this->list_members.end(); it++) {
            to_return.push_back(it->get());
        }
        return to_return;
    }

    void list_expression::add_item(std::unique_ptr<expression_base> to_add, const size_t index) {
        if (index <= this->list_members.size()) {
            auto it = this->list_members.begin() + index;
            this->list_members.insert(
                it,
                std::move(to_add)
            );
        }
        else {
            throw std::out_of_range("list_expression out of range");
        }
    }

    list_expression::list_expression(std::vector<std::unique_ptr<expression_base>>& list_members, enumerations::primitive_type list_type)
        : expression_base(enumerations::expression_type::LIST)
        , primary(list_type)
    {
        for (auto it = list_members.begin(); it != list_members.end(); it++)
        {
            this->list_members.push_back(std::move(*it));
        }
    }

    list_expression::list_expression(std::unique_ptr<expression_base> arg, enumerations::primitive_type list_type)
        : expression_base(enumerations::expression_type::LIST)
        , primary(list_type)
    {
        this->list_members.push_back(std::move(arg));
    }

    list_expression::list_expression()
        : expression_base(enumerations::expression_type::LIST)
    {
        this->primary = enumerations::primitive_type::NONE;	
    }
}
