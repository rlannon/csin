#include "symbol_table.hpp"

namespace utility
{
    void symbol_table::add_symbol(symbol&& sym)
    {
        auto it = _symbols.insert(
            std::make_pair<>(
                sym.get_name(),
                std::make_unique<symbol>(std::move(sym))
            )
        );
        
        if (!it.second)
        {
            throw error::compiler_exception("Could not add symbol to table.");
        }
    }

    bool symbol_table::contains(const std::string& name,
                                const std::vector<std::string>& scope,
                                const data_type& type) const
    {
        auto it = _symbols.find(symbol::decorate(name, scope, type));
        return it != _symbols.end();
    }

    symbol_table::~symbol_table() { }
}
