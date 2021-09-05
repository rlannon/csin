#include "declaration.hpp"

namespace statement
{
    const std::string& declaration::get_name() const {
        return this->name;
    }

    data_type& declaration::get_type_information() {
        return this->type;
    }

    const data_type& declaration::get_type_information() const
    {
        return this->type;
    }

    bool declaration::is_function() const
    {
        return this->function_definition;
    }

    bool declaration::is_struct() const
    {
        return this->struct_definition;
    }

    expression::expression_base* declaration::get_initial_value()
    {
        return this->initial_value.get();
    }

    std::vector<statement_base*> declaration::get_formal_parameters() {
        std::vector<statement_base*> to_return;
        for (auto it = this->formal_parameters.begin(); it != this->formal_parameters.end(); it++) {
            to_return.push_back(it->get());
        }
        return to_return;
    }

    std::vector<const statement_base*> declaration::get_formal_parameters() const {
        std::vector<const statement_base*> to_return;
        for (auto it = this->formal_parameters.begin(); it != this->formal_parameters.end(); it++) {
            to_return.push_back(it->get());
        }
        return to_return;
    }

    declaration::declaration(   const data_type& type, 
                                const std::string& var_name, 
                                std::unique_ptr<expression::expression_base>&& initial_value, 
                                bool is_function, 
                                bool is_struct)
        : statement_base(enumerations::statement_type::DECLARATION)
        , type(type)
        , name(var_name)
        , initial_value(std::move(initial_value))
        , function_definition(is_function)
        , struct_definition(is_struct) { }

    declaration::declaration(   const data_type& type,
                                const std::string& var_name, 
                                std::unique_ptr<expression::expression_base>&& initial_value, 
                                bool is_function, 
                                bool is_struct, 
                                std::vector<std::unique_ptr<statement_base>>& formal_parameters)
        : declaration(type, var_name, std::move(initial_value), is_function, is_struct)
        {
            for (auto it = formal_parameters.begin(); it != formal_parameters.end(); it++)
            {
                this->formal_parameters.push_back(std::move(*it));
            }
        }

    declaration::declaration()
        : declaration(data_type(), "", nullptr, false, false) { }
}
