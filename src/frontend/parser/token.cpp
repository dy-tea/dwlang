#include "token.h"

#include <iostream>

namespace frontend::parser {
    std::string token::to_string() const {
        switch (type) {
            case STRING:
                break;
            case LINECOUNT:
                break;
            case COMMENT:
                break;
            case KEYWORD:
                break;
            case IDENT:
                break;
            case NUM:
                break;
            case WS:
                break;
            case VERBATIM: {
                auto& [d] = std::get<token_::token_verbatim>(value);
                return std::string("[TOKEN]verbatim {\n") + d + "\n}";
            }
            case SCOPE_OPEN:
                break;
            case SCOPE_CLOSE:
                break;
            case PAREN_OPEN:
                break;
            case PAREN_CLOSE:
                break;
            case SQUARE_OPEN:
                break;
            case SQUARE_CLOSE:
                break;
        }

        return "";
    }
}
