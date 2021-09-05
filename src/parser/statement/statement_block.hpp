#pragma once

#include "statement.hpp"

#include <vector>
#include <memory>

namespace statement
{
    class statement_block
    {
    public:
        std::vector<std::shared_ptr<statement_base>> statements_list;   // todo: move to unique_ptr
        bool has_return;

        statement_block();
        ~statement_block();
    };
}
