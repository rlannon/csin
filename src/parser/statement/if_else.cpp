#include "if_else.hpp"

namespace statement
{
    const expression::expression_base& if_else::get_condition() const {
        return *this->condition.get();
    }

    const statement_base* if_else::get_if_branch() const {
        return this->if_branch.get();
    }

    const statement_base* if_else::get_else_branch() const {
        return this->else_branch.get();
    }

    if_else::if_else(   std::unique_ptr<expression::expression_base>&& condition_ptr,
                        std::unique_ptr<statement_base>&& if_branch_ptr,
                        std::unique_ptr<statement_base>&& else_branch_ptr)
        : statement_base(enumerations::statement_type::IF_THEN_ELSE)
        , condition(std::move(condition_ptr))
        , if_branch(std::move(if_branch_ptr))
        , else_branch(std::move(else_branch_ptr)) { }

    if_else::if_else(   std::unique_ptr<expression::expression_base>&& condition_ptr, 
                        std::unique_ptr<statement_base>&& if_branch_ptr)
        : if_else(std::move(condition_ptr), std::move(if_branch_ptr), nullptr) {}

    if_else::if_else(): statement_base(enumerations::statement_type::IF_THEN_ELSE) {}
}
