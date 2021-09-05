#pragma once

#include "statement.hpp"
#include "../../util/data_type.hpp"
#include "../expression/identifier.hpp"

#include <string>

namespace statement
{
    class allocation : public statement_base
    {
        data_type type_information;
        std::string value;
        bool initialized;

        expression::identifier struct_name;
        std::unique_ptr<expression::expression_base> initial_value;
    public:
        data_type& get_type_information();
        const data_type& get_type_information() const;
        static std::string get_var_type_as_string(enumerations::primitive_type to_convert);
        const std::string& get_name() const;

        bool was_initialized() const;
        const expression::expression_base* get_initial_value() const;

        allocation( const data_type& type_information, 
                    const std::string& value, 
                    const bool was_initialized = false, 
                    std::unique_ptr<expression::expression_base>&& initial_value = nullptr);
        allocation();
        virtual ~allocation() = default;
    };
}
