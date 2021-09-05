#include "keyword.hpp"

namespace expression
{
    const std::string& keyword::get_keyword() const {
        return this->_keyword;
    }

    const data_type &keyword::get_type() const {
        return this->_type;
    }

    bool keyword::has_type_information() const {
        return true;
    }

    void keyword::override_qualities(symbol_qualities sq) {
        this->_type.add_qualities(sq);
    }

    keyword::keyword(const std::string& kwd)
        : expression_base(enumerations::expression_type::KEYWORD_EXP)
        , _keyword(kwd) { }

    keyword::keyword(const data_type& t)
        : _keyword("")
        , _type(t) { }

    keyword::keyword(const data_type& t, const std::string& kwd)
        : expression_base(enumerations::expression_type::KEYWORD_EXP)
        , _type(t)
        , _keyword(kwd) { }
}
