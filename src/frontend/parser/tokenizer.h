#pragma once

#include <sstream>
#include <vector>

#include "token.h"

namespace driver {
    class compile_context;
}

namespace frontend::parser {
    class tokenizer {
        std::stringstream filebuffer;

    public:
        [[nodiscard]] std::vector<token> tokenize_fully(const driver::compile_context& ctx);

    private:
        void load(const driver::compile_context& ctx);
    };
}
