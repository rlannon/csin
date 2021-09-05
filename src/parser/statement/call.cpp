#include "call.hpp"

namespace statement
{
    call::call(expression::call& call_exp) 
        : statement_base(enumerations::statement_type::CALL)
        , expression::call(call_exp) { }

    call::call(): statement_base(enumerations::statement_type::CALL) { }
}
