#pragma once

#include "expression.hpp"

namespace expression
{
    class construction : public expression_base
    {
    public:
        class constructor
        {
            std::unique_ptr<expression_base> _member;	// this should probably always be an identifier
            std::unique_ptr<expression_base> _value;
        public:
            inline const expression_base& get_member() const
            {
                return *_member;
            }

            inline const expression_base& get_value() const
            {
                return *_value;
            }

            constructor(std::unique_ptr<expression_base>& member, std::unique_ptr<expression_base>& value)
                : _member(std::move(member))
                , _value(std::move(value)) { }
            constructor(const constructor& other)
                : _member(other._member->clone())
                , _value(other._value->clone()) { }
            ~constructor() = default;
        };

        inline const constructor* get_initializer(const size_t index) const noexcept
        {
            if (index < _initializers.size())
                return &_initializers.at(index);
            else
                return nullptr;
        }

        inline bool has_explicit_type() const noexcept { return _has_explicit_type; }
        inline const std::string& get_explicit_type() const noexcept { return _explicit_type; }
        inline bool has_default() const noexcept { return _has_default; }
        
        inline void set_explicit_type(const std::string& type_name)
        {
            this->_explicit_type = type_name;
            _has_explicit_type = true;
        }
        inline void set_default()
        {
            this->_has_default = true;
        }

        inline const std::vector<constructor>& get_initializers() const noexcept
        {
            return this->_initializers;
        }

        inline size_t num_initializations() const noexcept
        {
            return _initializers.size();
        }

        virtual std::unique_ptr<expression_base> clone() const override
        {
            std::vector<constructor> cloned_init;
            for (const auto& elem: _initializers)
            {
                cloned_init.push_back(elem);
            }

            return std::make_unique<construction>(std::move(cloned_init));
        }

        inline construction()
            : expression_base(enumerations::expression_type::CONSTRUCTION_EXP) { }
        inline construction(std::vector<constructor>&& initializers)
            : expression_base(enumerations::expression_type::CONSTRUCTION_EXP)
            , _initializers( std::move(initializers) ) { }
        
        virtual ~construction() = default;
    private:
        std::vector<constructor> _initializers;
        std::string _explicit_type;
        bool _has_explicit_type;
        bool _has_default;
    };
}
