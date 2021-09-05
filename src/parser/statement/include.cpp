#include "include.hpp"

namespace statement
{
    const std::string& include::get_filename() const {
        return this->filename;
    }

    include::include(const std::string& filename) 
        : statement_base(enumerations::statement_type::INCLUDE)
        , filename(filename) { }

    include::include(): include("") { }
}
