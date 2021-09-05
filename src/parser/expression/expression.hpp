#pragma once

#include "../../util/enumerated_types.hpp"
#include "../../util/symbol_qualities.hpp"

#include <memory>
#include <utility>

namespace expression
{
    /**
     * The base class for all expression types.
     */
    class expression_base
    {
    protected:
        bool _const;	// if we have the 'constexpr' keyword, this will be set
        bool _overridden;
        enumerations::expression_type _expression_type;	// replace "string type" with "expression_type expression_type"
    public:
        bool is_const() const;
        void set_const();
        enumerations::expression_type get_expression_type() const;

        virtual void override_qualities(symbol_qualities sq);
        virtual bool has_type_information() const;
        bool was_overridden() const;

        virtual std::unique_ptr<expression_base> clone() const = 0;

        expression_base(const enumerations::expression_type expression_type);
        expression_base();

        virtual ~expression_base() = 0;
    };
}
