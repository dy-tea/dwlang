#pragma once
#include <string>
#include <variant>

namespace frontend::parser {
    namespace token_ {
        struct token_string {
            std::string data;
        };

        struct token_line {
            std::size_t line;
        };

        struct token_comment {
            std::string data;
        };

        struct token_keyword {
            std::string data;
        };

        struct token_ident {
            std::string data;
        };

        struct token_number {
            std::string prefix;
            std::string data;
            std::string suffix;
        };

        struct token_verbatim {
            std::string data;
        };
    }

    struct token {
        enum token_type {
            STRING,
            LINECOUNT,
            COMMENT,
            KEYWORD,
            IDENT,
            NUM,
            WS, // whitespace
            VERBATIM, // special block.

            // symbols
            SCOPE_OPEN,
            SCOPE_CLOSE,
            PAREN_OPEN,
            PAREN_CLOSE,
            SQUARE_OPEN,
            SQUARE_CLOSE,
            ANGLE_OPEN,
            ANGLE_CLOSE,
        } type;

        std::variant<std::monostate, // provided for symbols who don't need data.
                     token_::token_string, token_::token_line, token_::token_comment, token_::token_keyword,
                     token_::token_ident, token_::token_number, token_::token_verbatim> value;

        [[nodiscard]] std::string to_string() const;
    };
}
