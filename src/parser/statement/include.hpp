#pragma once

#include "statement.hpp"

namespace statement
{
    class include : public statement_base
    {
        std::string filename;
    public:
        const std::string& get_filename() const;
        
        include(const std::string& filename);
        include();
        virtual ~include() = default;
    };
}
