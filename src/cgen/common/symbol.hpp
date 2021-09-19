#pragma once

#include "../../util/enumerated_types.hpp"
#include "../../util/data_type.hpp"

#include <vector>
#include <string>

/**
 * The base class for all symbols.
 */
class symbol
{
    bool _is_parameter;

protected:
    /**
     * The simple name for the symbol.
     */
    std::string _name;
    /**
     * The decorated name for the symbol.
     * 
     * This is stored within the symbol to increase efficiency.
     */
    std::string _decorated_name;
    /**
     * Indicates whether it is a piece of data, function, etc.
     */
    enumerations::symbol_type _symbol_type;
    /**
     * The data type of the symbol.
     * 
     * For a function, this type indicates the return type.
     */
    data_type _type;
    
    /**
     * The informaiton for the full symbol scope.
     */
    std::vector<std::string> _scope;

    bool _defined;
    size_t _line_defined;

    bool _initialized;
    bool _freed;

public:
    /**
     * Generates the decorated name for a symbol with a given name, scope, and type.
     */
    static std::string decorate(const std::string& name,
                                const std::vector<std::string>& scope, 
                                const data_type& type);
    static std::string decorate(const symbol& sym)
    {
        return decorate(sym.get_name(), sym.get_scope(), sym.get_type());
    }

    bool operator==(const symbol& right) const;
    bool operator!=(const symbol& right) const
    {
        return !this->operator==(right);
    }

    enumerations::symbol_type get_symbol_type() const { return _symbol_type; }

    void set_as_parameter() { _is_parameter = true; }

    const std::string& get_name() const { return _name; }

    const std::vector<std::string>& get_scope() const
    {
        return _scope;
    }

    /**
     * Checks whether this symbol is accessible from scope `other`.
     */
    bool is_accessible_from(const std::vector<std::string>& other) const noexcept;

    const data_type& get_type() const { return _type; }

    bool is_defined() const { return _defined; }
    void set_defined() { _defined = true; }
    
    bool initialized() const { return _initialized; }
    void set_initialized() { _initialized = true; }

    size_t get_line_defined() const { return _line_defined; }
    void set_line_defined(const size_t line) { _line_defined = line; }

    symbol& operator=(const symbol& other) = default;
    symbol& operator=(symbol&& other) = default;

    symbol( const std::string& name,
            const std::vector<std::string>& scope,
            const data_type& type,
            const bool defined=true,
            const size_t line_defined=0 );
    symbol(const symbol& other) = default;
    symbol(symbol&& other) = default;
    symbol() = default;
    virtual ~symbol();
};
