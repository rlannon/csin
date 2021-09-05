#pragma once

#include "statement.hpp"
#include "statement_block.hpp"

namespace statement
{
    class scoped_block: public statement_base
    {
        statement_block statements;
    public:
        const statement_block& get_statements() const;
        
        scoped_block(const statement_block& statements);
        virtual ~scoped_block() = default;
    };
}
