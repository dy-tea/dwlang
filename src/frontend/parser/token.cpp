#include "token.h"

#include <iostream>

namespace frontend::parser {
    std::string token::to_string() const {
        switch (type) {
            case STRING: {
                auto& [str] = std::get<token_::token_string>(value);
                return "[TOKEN] STR: " + str;
            }
            case LINECOUNT: {
                auto& [ln] = std::get<token_::token_line>(value);
                return "[TOKEN] LINE " + std::to_string(ln);
            }
            case COMMENT: {
                auto& [d] = std::get<token_::token_comment>(value);
                return "[TOKEN] /*" + d + "*/";
            }
            case KEYWORD: {
                auto& [d] = std::get<token_::token_keyword>(value);
                return std::string("[TOKEN] KEYWORD: ") + d;
            }
            case IDENT: {
                auto& [d] = std::get<token_::token_ident>(value);
                return std::string("[TOKEN] IDENT: ") + d;
            }
            case NUM: {
                auto& [d] = std::get<token_::token_number>(value);
                return std::string("[TOKEN] NUM: ") + d;
            }
            case WS: {
                return "[TOKEN] WHITESPACE";
            }
            case VERBATIM: {
                auto& [d] = std::get<token_::token_verbatim>(value);
                return std::string("[TOKEN] VERBATIM {\n") + d + "\n}";
            }
            case SCOPE_OPEN:
                return "[TOKEN] {";
            case SCOPE_CLOSE:
                return "[TOKEN] }";
            case PAREN_OPEN:
                return "[TOKEN] (";
            case PAREN_CLOSE:
                return "[TOKEN] )";
            case SQUARE_OPEN:
                return "[TOKEN] [";
            case SQUARE_CLOSE:
                return "[TOKEN] ]";
            case ANGLE_OPEN:
                return "[TOKEN] <";
            case ANGLE_CLOSE:
                return "[TOKEN] >";
            case UNKNOWN: {
                auto& [v] = std::get<token_::token_unknown>(value);
                return std::string("[TOKEN] UNK") + (char)v;
            }
            case BANG:
                return "[TOKEN] !";
            case TILDE:
                return "[TOKEN] ~";
            case PERCENT:
                return "[TOKEN] %";
            case HAT:
                return "[TOKEN] ^";
            case AMPERSAND:
                return "[TOKEN] &";
            case STAR:
                return "[TOKEN] *";
            case DASH:
                return "[TOKEN] -";
            case PLUS:
                return "[TOKEN] +";
            case EQ:
                return "[TOKEN] =";
            case PIPE:
                return "[TOKEN] |";
            case COMMA:
                return "[TOKEN] ,";
            case SEMICOLON:
                return "[TOKEN] ;";
            case COLON:
                return "[TOKEN] :";
            case SLASH:
                return "[TOKEN] /";
            case QUESTION:
                return "[TOKEN] ?";
        }

        return "[TOKEN] UNHANDLED to_string()";
    }
}
