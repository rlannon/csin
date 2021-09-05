#pragma once

#include "statement.hpp"
#include "../expression/construction.hpp"

namespace statement
{
    class construction : public statement_base
    {
        // When used as a statement, a construction takes a particular object to construct
        std::unique_ptr<expression::expression_base> _to_construct;
        std::unique_ptr<expression::construction> _construction;
    public:
        inline const expression::expression_base& get_to_construct() const
        {
            return *_to_construct;
        }

        inline const expression::construction& get_construction() const
        {
            return *_construction;
        }

        construction(   std::unique_ptr<expression::expression_base>&& to_construct, 
                        std::unique_ptr<expression::construction>&& construction)
            : statement_base(enumerations::statement_type::CONSTRUCTION_STATEMENT)
            , _to_construct(std::move(to_construct))
            , _construction(std::move(construction)) { }

        virtual ~construction() = default;
    };
}
