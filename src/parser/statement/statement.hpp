#pragma once

#include "../../util/enumerated_types.hpp"

#include <memory>
#include <string>

namespace statement
{
    class statement_base
    {
    protected:
        enumerations::statement_type _type;	// tells us whether its an allocation, and assignment, an ITE...
        std::string scope_name;	// to track the scope name under which the statement is being executed
        unsigned int scope_level;	// to track the scope level
        unsigned int _line;	// the line number on which the first token of the statement can be found in the file

        // TODO: add scope information to statements in parser

    public:
        enumerations::statement_type get_statement_type() const;

        unsigned int get_line_number() const;
        void set_line_number(unsigned int line_number);

        statement_base();
        statement_base(const enumerations::statement_type type);
        statement_base(const enumerations::statement_type type, const unsigned int line_number);
        virtual ~statement_base() = 0;
    };
}
