#pragma once

#include "expression.hpp"
#include "../../util/enumerated_types.hpp"
#include "../../util/data_type.hpp"

#include <string>

namespace expression
{
    class binary;

    class attribute_selection : public expression_base
    {
        std::unique_ptr<expression_base> selected;
        enumerations::attribute attrib;
        data_type t;
    public:
        static enumerations::attribute to_attribute(const std::string& to_convert);
        static bool is_attribute(const std::string& a);

        const expression_base &get_selected() const;
        enumerations::attribute get_attribute() const;
        const data_type &get_data_type() const;

        inline virtual std::unique_ptr<expression_base> clone() const override
        {
            auto c = std::make_unique<attribute_selection>(selected->clone(), attrib, t);
            return c;
        }

        attribute_selection(attribute_selection &old);
        attribute_selection(std::unique_ptr<expression_base>&& selected, const std::string& attribute_name);
        attribute_selection(std::unique_ptr<binary>&& to_deconstruct);
        attribute_selection(std::unique_ptr<expression_base>&& selected, enumerations::attribute attrib, const data_type& t);
        virtual ~attribute_selection() = default;
    };
}
