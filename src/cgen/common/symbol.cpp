#include "symbol.hpp"

#include <sstream>

std::string symbol::decorate(   const std::string& name,
                                const std::vector<std::string>& scope,
                                const data_type& type)
{
    std::stringstream decorated;
    decorated << "_SIN_";

    decorated << "N";
    for (const auto& s: scope)
    {
        decorated << scope.size() << scope;
    }
    decorated << "E@" << name << "@" << type.decorate();

    return decorated.str();
}

std::string symbol::decorate(const symbol& sym)
{
    return decorate(sym.get_name(), sym.get_type());
}

symbol::symbol( const std::string& name,
                const std::string& scope_name,
                const size_t scope_level,
                const data_type& type,
                const bool defined=true,
                const size_t line_defined=0 )
    : _name(name)
    , _scope_name(scope_name)
    , _scope_level(scope_level)
    , _type(type)
    , _defined(defined)
    , _line_defined(line_defined)
    {
        _decorated_name = decorate(_name, _type);
    }

symbol::~symbol() {}
