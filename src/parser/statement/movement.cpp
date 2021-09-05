#include "movement.hpp"

namespace statement
{
    movement::movement( std::unique_ptr<expression::expression_base>&& lvalue, 
                        std::unique_ptr<expression::expression_base>&& rvalue)
        : assignment(std::move(lvalue), std::move(rvalue))
    {
        this->_type = enumerations::statement_type::MOVEMENT;
    }
}
