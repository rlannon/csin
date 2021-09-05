#include "compound_assignment.hpp"
#include "../expression/binary.hpp"

namespace statement
{
    enumerations::exp_operator compound_assignment::get_operator() const
    {
        return _op;
    }

    compound_assignment::compound_assignment(   std::unique_ptr<expression::expression_base>&& lvalue,
                                                std::unique_ptr<expression::expression_base>&& rvalue,
                                                enumerations::exp_operator op)	
        : assignment(std::move(lvalue)
        , std::make_unique<expression::binary>(lvalue->clone(), std::move(rvalue), op))
        {
            this->_type = enumerations::statement_type::COMPOUND_ASSIGNMENT;
        }

    compound_assignment::compound_assignment()
    {
        this->_type = enumerations::statement_type::COMPOUND_ASSIGNMENT;
    }
}
