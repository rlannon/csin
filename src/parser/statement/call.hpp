#pragma once

#include "statement.hpp"
#include "../expression/call.hpp"

namespace statement
{
    class call : public statement_base, public expression::call
    {
    public:
        call(expression::call& call_exp);
        call();
        virtual ~call() = default;
    };
}
