#pragma once

#include "statement.hpp"
#include "../expression/expression.hpp"
#include "../../util/data_type.hpp"

#include <string>

namespace statement
{
    class declaration : public statement_base
    {
        data_type type;
        bool function_definition;	// whether it's the declaration of a function
        bool struct_definition;	// whether it's the declaration of a struct

        std::string name;

        std::unique_ptr<expression::expression_base> initial_value;

        std::vector<std::unique_ptr<statement_base>> formal_parameters;
    
    public:
        const std::string& get_name() const;

        data_type& get_type_information();
        const data_type& get_type_information() const;

        bool is_function() const;
        bool is_struct() const;

        expression::expression_base* get_initial_value();

        std::vector<statement_base*> get_formal_parameters();
        std::vector<const statement_base*> get_formal_parameters() const;
        
        declaration(const data_type& type, 
                    const std::string& var_name,
                    std::unique_ptr<expression::expression_base>&& initial_value = nullptr, 
                    bool is_function = false, 
                    bool is_struct = false);
        declaration(const data_type& type, 
                    const std::string& var_name, 
                    std::unique_ptr<expression::expression_base>&& initial_value, 
                    bool is_function, 
                    bool is_struct,
                    std::vector<std::unique_ptr<statement_base>>& formal_parameters);
        declaration();
        virtual ~declaration() = default;
    };
}
