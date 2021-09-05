#pragma once

#include "definition.hpp"

namespace statement
{
    class struct_definition : public definition
    {
    public:
        struct_definition(const std::string& name, std::unique_ptr<statement_block>&& procedure);
        struct_definition();
        virtual ~struct_definition() = default;
    };
}
