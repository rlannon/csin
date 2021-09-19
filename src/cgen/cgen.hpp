#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "../parser/statements.hpp"
#include "common/symbol_table.hpp"

/**
 * The code generator class.
 */
class cgen
{
    bool _unsafe;
    bool _strict;
    bool _micro;

    /**
     * The symbols known by the generator.
     */
    utility::symbol_table _symbols;
    /**
     * The full nested scope name.
     */
    std::vector<std::string> _scope;
    /**
     * Contains the main text segment.
     */
    std::stringstream _text;
    /**
     * Contains the definitions for various structs defined here.
     */
    std::stringstream _struct_definitions;

    bool next();

    void generate_code(const statement::statement_block& ast);
    std::string gen_allocation(const statement::allocation& alloc);

public:
    void generate_code(const std::string& in_filename, std::string out_filename);

    cgen(bool allow_unsafe, bool use_strict, bool use_micro);
    ~cgen();
};
