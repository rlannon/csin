#include "while_loop.hpp"

namespace statement
{
    const expression::expression_base& while_loop::get_condition() const
    {
        return *this->condition.get();
    }

    const statement_base* while_loop::get_branch() const
    {
        return this->branch.get();
    }

    while_loop::while_loop(std::unique_ptr<expression::expression_base>&& condition, std::unique_ptr<statement_base>&& branch) 
        : statement_base(enumerations::statement_type::WHILE_LOOP)
        , condition(std::move(condition))
        , branch(std::move(branch)) { }

    while_loop::while_loop(): statement_base(enumerations::statement_type::WHILE_LOOP) { }
}
