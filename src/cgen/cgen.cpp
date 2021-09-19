#include "cgen.hpp"
#include "../parser/statements.hpp"
#include "../util/exceptions.hpp"
#include "../util/enumerated_types.hpp"

#include <utility>

cgen::cgen(bool allow_unsafe, bool use_strict, bool use_micro)
    : _unsafe(allow_unsafe)
    , _strict(use_strict)
    , _micro(use_micro) { }

cgen::~cgen() { }

void cgen::process_statement(const statement::statement_base& s)
{
    using s_type = enumerations::statement_type;
    using namespace statement;

    try
    {    
        switch (s.get_statement_type())
        {
        case s_type::ALLOCATION:
        {
            const allocation& alloc(dynamic_cast<const allocation&>(s));
            _text << gen_allocation(alloc);
            break;
        }
        case s_type::ASSIGNMENT:
        {
            break;
        }
        case s_type::COMPOUND_ASSIGNMENT:
        {
            break;
        }
        case s_type::CALL:
        {
            break;
        }
        case s_type::CONSTRUCTION_STATEMENT:
        {
            break;
        }
        case s_type::DECLARATION:
        {
            break;
        }
        case s_type::FUNCTION_DEFINITION:
        {
            break;
        }
        case s_type::IF_THEN_ELSE:
        {
            break;
        }
        case s_type::INCLUDE:
        {
            break;
        }
        case s_type::MOVEMENT:
        {
            break;
        }
        case s_type::RETURN_STATEMENT:
        {
            break;
        }
        case s_type::SCOPED_BLOCK:
        {
            break;
        }
        case s_type::STRUCT_DEFINITION:
        {
            break;
        }
        case s_type::WHILE_LOOP:
        {
            break;
        }
        default:
            throw error::compiler_exception("Unsupported statement type", error_code::UNSUPPORTED_FEATURE, s.get_line_number());
            break;
        };
    }
    catch (std::bad_cast& e)
    {
        throw error::compiler_exception("Could not process statement", error_code::UNSUPPORTED_ERROR, s.get_line_number());
    }
}

void cgen::generate_code(const statement::statement_block& ast)
{
    size_t error_count = 0;

    for (const auto& s: ast)
    {
        try
        {
            process_statement(s);   
        }
        catch(const std::exception& e)
        {
            error_count++;
            std::cerr << e.what() << '\n';
            
            if (error_count > 5)
                break;
        }
    }
}

void cgen::generate_code(const std::string& in_filename, std::string out_filename)
{

}
