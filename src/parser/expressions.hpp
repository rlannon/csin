#pragma once

/**
 * Includes all expression headers
 */

#include "expression/expression.hpp"
#include "expression/attribute_selection.hpp"
#include "expression/binary.hpp"
#include "expression/call.hpp"
#include "expression/construction.hpp"
#include "expression/identifier.hpp"
#include "expression/indexed.hpp"
#include "expression/keyword.hpp"
#include "expression/list_expression.hpp"
#include "expression/literal.hpp"
#include "expression/procedure.hpp"
#include "expression/typecast.hpp"
#include "expression/unary.hpp"

namespace expression
{
    /**
     * Determines whether a given lexeme type holds a literal expression
     */
    inline bool is_literal(const enumerations::lexeme_type candidate_type)
    {
        using lt = enumerations::lexeme_type;

        switch(candidate_type) {
            case lt::INT_LEX:
            case lt::FLOAT_LEX:
            case lt::BOOL_LEX:
            case lt::STRING_LEX:
            case lt::CHAR_LEX:
                return true;
            default:
                return false;
        }
    }
}
