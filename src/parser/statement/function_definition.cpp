#include "function_definition.hpp"

namespace statement
{
    const data_type& function_definition::get_type_information() const
    {
        return this->return_type;
    }

    std::vector<const statement_base*> function_definition::get_formal_parameters() const {
        std::vector<const statement_base*> to_return;
        for (auto it = this->formal_parameters.begin(); it != this->formal_parameters.end(); it++) {
            to_return.push_back(it->get());
        }
        return to_return;
    }

    function_definition::function_definition(   const std::string& name,
                                                const data_type& return_type,
                                                std::vector<std::unique_ptr<statement_base>>& args_ptr,
                                                std::unique_ptr<statement_block>&& procedure_ptr)
        : definition(name, std::move(procedure_ptr))
        , return_type(return_type)
    {
        for (auto it = args_ptr.begin(); it != args_ptr.end(); it++)
        {
            this->formal_parameters.push_back(std::move(*it));
        }
        this->_type = enumerations::statement_type::FUNCTION_DEFINITION;
    }

    function_definition::function_definition()
        : definition()
    {
        this->_type = enumerations::statement_type::FUNCTION_DEFINITION;
    }
}
