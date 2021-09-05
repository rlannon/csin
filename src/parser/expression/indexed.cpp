#include "indexed.hpp"

namespace expression
{
    const expression_base &indexed::get_index_value() const
    {
        return *this->index_value.get();
    }

    const expression_base &indexed::get_to_index() const
    {
        return *this->to_index.get();
    }

    indexed::indexed(   std::unique_ptr<expression_base> to_index, 
                        std::unique_ptr<expression_base> index_value)
        : expression_base(enumerations::expression_type::INDEXED)
        , to_index(std::move(to_index))
        , index_value(std::move(index_value)) {}

    indexed::indexed()
        : indexed(nullptr, nullptr) {}
}
