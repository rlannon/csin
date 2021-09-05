#include "typecast.hpp"
#include "keyword.hpp"

namespace expression
{
    const expression_base &typecast::get_exp() const {
        return *this->to_cast;
    }

    const data_type& typecast::get_new_type() const {
        return this->new_type;
    }

    typecast::typecast(typecast &old): expression_base(enumerations::expression_type::CAST) {
        this->new_type = old.new_type;
        this->to_cast = std::move(old.to_cast);
    }

    typecast::typecast(std::unique_ptr<expression_base> to_cast, const data_type& new_type)
        : expression_base(enumerations::expression_type::CAST)
        , to_cast(std::move(to_cast))
        , new_type(new_type) { }

    typecast::typecast(std::unique_ptr<binary> b): expression_base(enumerations::expression_type::CAST) {
        if (b->get_operator() == enumerations::exp_operator::TYPECAST && 
            b->get_right().get_expression_type() == enumerations::expression_type::KEYWORD_EXP) 
        {
            auto &kw = static_cast<const keyword&>(b->get_right());
            this->to_cast = std::move( b->get_left_unique() );
            this->new_type = kw.get_type();
        }
        else {
            this->_expression_type = enumerations::expression_type::EXPRESSION_GENERAL;
            this->to_cast = nullptr;
        }
    }
}
