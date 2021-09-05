#include "parser.hpp"

std::unique_ptr<statement::statement_base> parser::parse_construction()
{
    this->next();
    auto to_construct = this->parse_expression(true);   // allow a brace after this expression
    auto body = this->parse_construction_body();

    // ensure we end with a curly brace
    if (this->peek().value == "}")
    {
        this->next();
    }
    else
    {
        throw error::compiler_exception(
            "Expected closing curly brace",
            error_code::MISSING_GROUPING_SYMBOL_ERROR,
            this->current_token().line_number
        );
    }

    return std::make_unique<statement::construction>(std::move(to_construct), std::move(body));
}

std::unique_ptr<expression::construction> parser::parse_construction_body(const bool has_type, const std::string& explicit_type)
{
    if (this->next().value == "{")
    {
        std::vector<expression::construction::constructor> initializers;
        bool has_default = false;
        bool is_const = true;   // assume it can be deduced at compile-time (all expressions must be for this to remain true)

        while (this->peek().type != enumerations::lexeme_type::KEYWORD_LEX && this->peek().value != "}")
        {
            // Expression parsing begins on the first token of the expression
            this->next();
            auto member = this->parse_expression(0UL, "(", false, true);    // all defaults except 'omit_equals'
            
            // we should see a colon, then the initialization expression
            if (this->peek().value == ":")
            {
                this->next();   // skip colon; skip ahead to first character of initialization
                this->next();
                
                auto value = this->parse_expression();
                is_const = is_const && value->is_const();

                initializers.push_back(
                    expression::construction::constructor{member, value}
                );

                // we are now on the last lexeme of the expression; the next should be a comma
                if (this->peek().value == ",")
                {
                    this->next();
                }
                else if (this->peek().value != "}")
                {
                    throw error::compiler_exception(
                        "Expected commas between expressions",
                        error_code::EXPECTED_LIST_INITIALIZATION,
                        this->current_token().line_number
                    );
                }
            }
            else
            {
                throw error::compiler_exception("Expected initialization", error_code::EXPECTED_INITIALIZATION, this->peek().line_number);
            }
        }

        // we may have ended in 'default'
        if (this->peek().value == "default")
        {
            this->next();
            has_default = true;
            
            // we are allowed to have a comma after the last expression
            if (this->peek().value == ",")
            {
                this->next();
            }

            // we must end the expression here
            if (this->peek().value != "}")
            {
                throw error::compiler_exception(
                    "Expected closing curly brace after 'default",
                    error_code::MISSING_GROUPING_SYMBOL_ERROR,
                    this->current_token().line_number
                );
            }
        }

        auto ctor = std::make_unique<expression::construction>(std::move(initializers));
        if (has_type)
            ctor->set_explicit_type(explicit_type);
        
        if (has_default)
            ctor->set_default();
        
        if (is_const)
            ctor->set_const();
        
        return ctor;
    }
    else
    {
        throw error::compiler_exception(
            "Expected a block",
            error_code::MISSING_GROUPING_SYMBOL_ERROR,
            this->current_token().line_number
        );
    }
}
