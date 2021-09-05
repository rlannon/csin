#include "allocation.hpp"

#include <array>

namespace statement
{
    data_type& allocation::get_type_information() {
        return this->type_information;
    }

    const data_type& allocation::get_type_information() const {
        return this->type_information;
    }

    std::string allocation::get_var_type_as_string(enumerations::primitive_type to_convert)
    {
        using pt = enumerations::primitive_type;

        const size_t num_types = 4;
        std::array<std::string, 4> types_list = { "int", "float", "string", "bool" };
        std::array<pt, 4> types = { pt::INT, pt::FLOAT, pt::STRING, pt::BOOL };

        for (size_t i = 0; i < types.size(); i++) {
            if (to_convert == types[i]) {
                return types_list[i];
            }
        }

        // if we get here, the type was not in the list
        return "[unknown type]";
    }

    const std::string& allocation::get_name() const {
        return this->value;
    }

    bool allocation::was_initialized() const
    {
        return this->initialized;
    }

    const expression::expression_base *allocation::get_initial_value() const
    {
        return this->initial_value.get();
    }

    allocation::allocation( const data_type& type_information,
                            const std::string& value, 
                            const bool initialized, 
                            std::unique_ptr<expression::expression_base>&& initial_value) 
        : statement_base(enumerations::statement_type::ALLOCATION)
        , type_information(type_information)
        , value(value)
        , initialized(initialized)
        , initial_value(std::move(initial_value)) { }

    allocation::allocation()
        : statement_base(enumerations::statement_type::ALLOCATION) { }
}
