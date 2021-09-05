#include "statement.hpp"

namespace statement
{
    enumerations::statement_type statement_base::get_statement_type() const {
        return statement_base::_type;
    }

    unsigned int statement_base::get_line_number() const
    {
        return this->_line;
    }

    void statement_base::set_line_number(unsigned int line_number)
    {
        this->_line = line_number;
    }

    statement_base::statement_base() {
        this->scope_level = 0;
        this->scope_name = "global";
    }

    statement_base::statement_base(const enumerations::statement_type type) {
        this->_type = type;
    }

    statement_base::statement_base(const enumerations::statement_type type, const unsigned int line_number)
        : _type(type)
        , _line(line_number) {}
    
    statement_base::~statement_base() {}
}