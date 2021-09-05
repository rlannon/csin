#pragma once

#include "statement.hpp"
#include "statement_block.hpp"

#include <string>

namespace statement
{
    class definition: public statement_base
    {
        // The parent class for definitions
    protected:
        std::string name;
        std::unique_ptr<statement_block> procedure;
    public:
        const std::string& get_name() const;
        const statement_block& get_procedure() const;

        definition(const std::string& name, std::unique_ptr<statement_block>&& procedure);
        definition();
        virtual ~definition() = default;
    };
}
