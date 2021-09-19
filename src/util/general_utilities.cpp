#include "general_utilities.hpp"
#include "enumerated_types.hpp"
#include "exceptions.hpp"

bool general_utilities::returns(const statement::statement_block& to_check) {
	if (to_check.has_return) {
		return true;
	} else {
		bool to_return = true;

		// iterate through statements to see if we have an if/else block; if so, check *those* for return values
		auto it = to_check.statements_list.begin();
		while (it != to_check.statements_list.end() && to_return) {
			// get the statement pointer
            std::shared_ptr<statement::statement_base> s = *it;

            // handle ite
			if (s->get_statement_type() == enumerations::statement_type::IF_THEN_ELSE) {
                to_return = ite_returns(static_cast<statement::if_else*>(s.get()));
			}

			it++;
		}

		return to_return;
	}
}

bool general_utilities::returns(const statement::statement_base& to_check) {
    if (to_check.get_statement_type() == enumerations::statement_type::SCOPED_BLOCK) {
        auto &block = static_cast<const statement::scoped_block&>(to_check);
        return returns(block.get_statements());
    }
    else {
        return to_check.get_statement_type() == enumerations::statement_type::RETURN_STATEMENT;
    }
}

bool general_utilities::ite_returns(const statement::if_else *to_check) {
    // both must be true for it to return true
    bool if_returns = false;
    if (to_check->get_if_branch())
        if_returns = returns(*to_check->get_if_branch());
    
    bool else_returns = false;
    if (to_check->get_else_branch())
        else_returns = returns(*to_check->get_else_branch());

    return if_returns && else_returns;
}

bool general_utilities::is_bitwise(const enumerations::exp_operator op) {
    return (op == enumerations::exp_operator::BIT_AND || 
            op == enumerations::exp_operator::BIT_OR || 
            op == enumerations::exp_operator::BIT_XOR || 
            op == enumerations::exp_operator::BIT_NOT);
}
