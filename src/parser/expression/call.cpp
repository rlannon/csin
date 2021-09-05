#include "call.hpp"
#include "../../util/enumerated_types.hpp"

namespace expression
{
    call::call(procedure *proc): procedure(*proc)
    {
        this->_expression_type = enumerations::expression_type::CALL_EXP;
    }

    call::call(call& other): procedure(other)
    {
        this->_expression_type = enumerations::expression_type::CALL_EXP;
    }

    call::call()
    {
        this->_expression_type = enumerations::expression_type::CALL_EXP;
    }

    call::~call() {}
}
