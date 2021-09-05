#include "definition.hpp"

namespace statement
{
    const std::string& definition::get_name() const {
        return this->name;
    }

    const statement_block& definition::get_procedure() const {
        return *this->procedure.get();
    }

    definition::definition(const std::string& name, std::unique_ptr<statement_block>&& procedure)
        : statement_base()
        , name(name)
        , procedure(std::move(procedure)) {}

    definition::definition() {}
}
