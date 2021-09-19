#include "../cgen.hpp"
#include "../../parser/statement/allocation.hpp"

using statement::allocation;

cgen::gen_allocation(const allocation& alloc)
{
    std::stringstream code;

    _symbols.add_symbol(symbol {
                            alloc.get_name(),
                            _scope,
                            alloc.get_type_information(),
                            alloc.was_initialized(),
                            alloc.get_line_number()
                        });

    const data_type& t = alloc.get_type_information();
    code << t.get_c_typename() << " ";
    code << alloc.get_name();

    if (t.get_qualities().is_dynamic())
    {
        code << " = malloc(" << t.get_width() << ")";
    }

    code << ";\n";

    if (alloc.was_initialized())
    {
        // todo: alloc-init
    }

    return code.str();
}
