#include "procedure.hpp"
#include "list_expression.hpp"

namespace expression
{
    const expression_base &procedure::get_func_name() const {
        return *this->name.get();
    }

    const list_expression &procedure::get_args() const {
        return dynamic_cast<list_expression&>(*args);
    }

    const expression_base &procedure::get_arg(size_t arg_no) const {
        return *dynamic_cast<list_expression*>(args.get())->get_list().at(arg_no);
    }

    size_t procedure::get_num_args() const {
        return dynamic_cast<list_expression*>(args.get())->get_list().size();
    }

    void procedure::insert_arg(std::unique_ptr<expression_base> to_insert, const size_t index) {
        dynamic_cast<list_expression*>(args.get())->add_item(std::move(to_insert), index);
    }

    procedure::procedure(procedure& other)
        : expression_base(enumerations::expression_type::PROC_EXP)
        , name(std::move(other.name))
        , args(std::move(other.args))
    {
    }

    procedure::procedure(std::unique_ptr<expression_base> proc_name, std::unique_ptr<expression_base> proc_args)
        : expression_base(enumerations::expression_type::PROC_EXP)
        , name(std::move(proc_name))
        , args(std::move(proc_args)) { }

    procedure::procedure()
        : expression_base(enumerations::expression_type::PROC_EXP)
        , name(nullptr)
        , args(nullptr) { }

    procedure::~procedure() { }
}
