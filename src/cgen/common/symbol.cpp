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
        decorated << s.size() << s;
    }
    decorated << "E@" << name << "@" << type.decorate();

    return decorated.str();
}

bool symbol::is_accessible_from(const std::vector<std::string>& other) const noexcept
{
    if (other.size() > _scope.size())
    {
        for (size_t i = 0; i < _scope.size(); i++)
        {
            if (_scope[i] != other[i])
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

symbol::symbol( const std::string& name,
                const std::vector<std::string>& scope,
                const data_type& type,
                const bool defined,
                const size_t line_defined )
    : _name(name)
    , _scope(scope)
    , _type(type)
    , _defined(defined)
    , _line_defined(line_defined)
    {
        _decorated_name = decorate(_name, _scope, _type);
    }

symbol::~symbol() {}
