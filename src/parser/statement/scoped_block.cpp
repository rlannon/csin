#include "scoped_block.hpp"

namespace statement
{
    const statement_block& scoped_block::get_statements() const {
        return this->statements;
    }

    scoped_block::scoped_block(const statement_block& statements)
        : statement_base(enumerations::statement_type::SCOPED_BLOCK)
        , statements(statements) { }
}
