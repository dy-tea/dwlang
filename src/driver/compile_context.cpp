#include "compile_context.h"

#include <iostream>

#include "frontend/parser/parser.h"

namespace driver {
    int compile_context::compile() {
        frontend::parser::parser p;

        auto tokens = p.tokenize_fully(*this);

        // pretty print the tokens for now.
        for (const auto& t : tokens) {
            std::cout << t.to_string() << std::endl;
        }

        return 0;
    }
}
