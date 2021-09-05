#include "struct_definition.hpp"

namespace statement
{
    struct_definition::struct_definition(const std::string& name, std::unique_ptr<statement_block>&& procedure_ptr):
        definition(name, std::move(procedure_ptr))
    {
        this->_type = enumerations::statement_type::STRUCT_DEFINITION;
    }
}
