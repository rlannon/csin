#include "assignment.hpp"

namespace statement
{
    const expression::expression_base& assignment::get_lvalue() const {
        return *this->lvalue.get();
    }

    const expression::expression_base& assignment::get_rvalue() const {
        return *this->rvalue_ptr.get();
    }

    assignment::assignment(std::unique_ptr<expression::expression_base>&& lvalue, std::unique_ptr<expression::expression_base>&& rvalue) 
        : statement_base(enumerations::statement_type::ASSIGNMENT)
        , lvalue(std::move(lvalue)) 
        , rvalue_ptr(std::move(rvalue)) { }

    assignment::assignment(const expression::identifier& lvalue, std::unique_ptr<expression::expression_base>&& rvalue)
        : statement_base(enumerations::statement_type::ASSIGNMENT)
        , rvalue_ptr(std::move(rvalue))
        , lvalue(std::make_unique<expression::identifier>(lvalue)) { }

    assignment::assignment(): assignment(nullptr, nullptr) { }
}
