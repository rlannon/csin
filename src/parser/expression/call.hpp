#pragma once

#include "procedure.hpp"

namespace expression
{
    class call : public procedure
    {
    public:
        call(procedure *proc);
        call(call& other);
        call();
        virtual ~call() override;
    };
}
