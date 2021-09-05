#include "return.hpp"

namespace statement
{
    const expression::expression_base& return_statement::get_return_exp() const {
        return *this->return_exp.get();
    }

    return_statement::return_statement(std::unique_ptr<expression::expression_base>&& exp_ptr)
        : statement_base(enumerations::statement_type::RETURN_STATEMENT)
        , return_exp(std::move(exp_ptr)) { }

    return_statement::return_statement(): return_statement(nullptr) { }
}
