#pragma once

#include "symbol.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <utility>
#include <deque>

namespace utility
{
    /**
     * Contains the symbol table for the running code generator.
     */
    class symbol_table
    {
        /**
         * A node for the deque that contains scope exit information.
         */
        struct node
        {
            std::string name;
            std::string scope_name;
            size_t scope_level;

            node(   const std::string& name,
                    const std::string& scope_name,
                    const size_t scope_level )
                : name(name)
                , scope_name(scope_name)
                , scope_level(scope_level) {}
            node() = default;
            ~node() = default;
        };

        /**
         * The map of all existing symbols.
         * 
         * Note the key is a decorated name.
         */
        std::unordered_map<std::string, std::unique_ptr<symbol>> _symbols;
        /**
         * Local symbols that must be freed.
         */
        std::deque<node> _locals;
    };
}
