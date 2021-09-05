#pragma once

#include "definition.hpp"
#include "../../util/data_type.hpp"

namespace statement
{
    class function_definition : public definition
    {
        std::vector<std::unique_ptr<statement_base>> formal_parameters;
        data_type return_type;

    public:
        const data_type& get_type_information() const;
        std::vector<const statement_base*> get_formal_parameters() const;
        
        function_definition(const std::string& name,
                            const data_type& return_type,
                            std::vector<std::unique_ptr<statement_base>>& args_ptr,
                            std::unique_ptr<statement_block>&& procedure_ptr);
        function_definition();
        virtual ~function_definition() = default;
    };
}
