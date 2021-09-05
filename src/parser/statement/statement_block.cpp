#include "statement_block.hpp"

namespace statement
{
    statement_block::statement_block()
        : statement_list({})
        , has_return(false) { }

    statement_block::~statement_block() { }
}
