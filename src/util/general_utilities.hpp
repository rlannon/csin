#pragma once

#include "../parser/statements.hpp"

namespace general_utilities {
    const int BASE_PARAMETER_OFFSET = 16;

    bool returns(const statement::statement_block& to_check);
    bool returns(const statement::statement_base& to_check);
    bool ite_returns(const statement::if_else* to_check);
    bool is_bitwise(const enumerations::exp_operator op);
}
