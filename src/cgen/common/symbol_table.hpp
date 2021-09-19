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
         * The map of all existing symbols.
         * 
         * Note the key is a decorated name.
         */
        std::unordered_map<std::string, std::unique_ptr<symbol>> _symbols;
        /**
         * Local symbols that must be freed.
         * 
         * Note the deque contains the decorated symbol name.
         */
        std::deque<std::string> _locals;
    
    public:
        void add_symbol(symbol&& sym);
        bool contains(const std::string& name, const std::vector<std::string>& scope, const data_type& type) const;
        
        symbol_table() = default;
        ~symbol_table();
    };
}
