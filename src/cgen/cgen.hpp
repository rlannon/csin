#pragma once

#include <string>
#include <vector>

namespace statement
{
    class statement_block;
}

/**
 * The code generator class.
 */
class cgen
{
    bool _unsafe;
    bool _strict;
    bool _micro;

    std::vector<std::string> _scope;

    bool next();

    void generate_code(const statement_block& ast);

public:
    void generate_code(const std::string& in_filename, std::string out_filename);

    cgen(bool allow_unsafe, bool use_strict, bool use_micro);
    ~cgen();
};
