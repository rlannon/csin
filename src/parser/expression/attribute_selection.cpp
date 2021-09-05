#include "attribute_selection.hpp"
#include "keyword.hpp"
#include "binary.hpp"

namespace expression
{
    const expression_base &attribute_selection::get_selected() const {
        return *this->selected;
    }

    enumerations::attribute attribute_selection::get_attribute() const {
        return this->attrib;
    }

    const data_type &attribute_selection::get_data_type() const {
        return this->t;
    }

    enumerations::attribute attribute_selection::to_attribute(const std::string& to_convert) {
        if (to_convert == "len") {
            return enumerations::attribute::LENGTH;
        }
        else if (to_convert == "size") {
            return enumerations::attribute::SIZE;
        }
        else if (to_convert == "var") {
            return enumerations::attribute::VARIABILITY;
        }
        else {
            return enumerations::attribute::NO_ATTRIBUTE;
        }
    }

    bool attribute_selection::is_attribute(const std::string& a) {
        return to_attribute(a) != enumerations::attribute::NO_ATTRIBUTE;
    }

    attribute_selection::attribute_selection(attribute_selection &old)
        : expression_base(enumerations::expression_type::ATTRIBUTE)
        , selected(std::move(old.selected))
        , t(old.t)
        , attrib(old.attrib) { }

    attribute_selection::attribute_selection(std::unique_ptr<expression_base>&& selected, const std::string& attribute_name)
        : expression_base(enumerations::expression_type::ATTRIBUTE)
        , attrib( to_attribute(attribute_name) )
        , selected( std::move(selected) )
        , t(
            data_type{
                enumerations::primitive_type::INT,
                enumerations::primitive_type::NONE,
                symbol_qualities(
                    false,	// not const
                    false,	// not static
                    false,	// not dynamic
                    false	// not signed
                )	// not long, short, or extern
            }
        )
    {
        // all attributes are final; they are not necessarily known at compile time, but they are not directly modifiable
        this->t.get_qualities().add_quality(enumerations::symbol_quality::FINAL);
    }

    attribute_selection::attribute_selection(std::unique_ptr<binary>&& to_deconstruct)
        : expression_base(enumerations::expression_type::ATTRIBUTE)
    {
        // Construct an 'attribute_selection' object from a binary expression
        
        // as long as we have a valid binary expression, continue
        if (to_deconstruct->get_right().get_expression_type() == enumerations::expression_type::KEYWORD_EXP) {
            this->selected = std::move(to_deconstruct->get_left_unique());

            auto right = static_cast<const keyword&>(to_deconstruct->get_right());
            this->attrib = to_attribute(right.get_keyword());
        }
        else {
            this->_expression_type = enumerations::expression_type::EXPRESSION_GENERAL;
            this->selected = nullptr;
        }

        // set the attribute data type -- always returns 'int &unsigned final'
        this->t = data_type(
            enumerations::primitive_type::INT,
            enumerations::primitive_type::NONE,
            symbol_qualities(
                false,
                false,
                false,
                false,
                true
            )
        );
        
        // all attributes are final; they are not necessarily known at compile time, but they are not directly modifiable
        this->t.get_qualities().add_quality(enumerations::symbol_quality::FINAL);
    }

    attribute_selection::attribute_selection(   std::unique_ptr<expression_base>&& selected, 
                                                enumerations::attribute attrib, 
                                                const data_type& t  )
        : selected(std::move(selected))
        , attrib(attrib)
        , t(t) { }
}
