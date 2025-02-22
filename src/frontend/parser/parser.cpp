#include "parser.h"

#include <fstream>
#include <stack>
#include <unordered_set>

#include "driver/compile_context.h"

#include <common/utilities.h>

namespace frontend::parser {
    enum class tokenizer_state {
        DEFAULT,
        STRING,
        ESCAPED,
        SLCOMMENT, // singleline comment
        MLCOMMENT, // multiline comment
        IDENT,
        NUM,
        PRE_VERBATIM,
        VERBATIM,
    };

    std::vector<token> parser::tokenize_fully(const driver::compile_context &ctx) {
        using namespace token_;
        using namespace ice;

        load(ctx);

        std::unordered_set<std::string> keywords {
            "verbatim", // verbatim code emission directly into c++

            "include",
            "pub",
            "namespace",
            "fn",
            "class",
            "let",
            "if",
            "else",
            "while",
            "for",
            "return",
            "goto",
            "continue",
            "break",
            "switch",
            "case",
            "default",
            "inspect",

            // types
            "bool",
            "float",
            "double",
            "char",
            "u8",
            "u16",
            "u32",
            "u64",
            "i8",
            "i16",
            "i32",
            "i64",
            "void",

            // reserved:
            "asm", // reserved for inline assembly
            "operator", // reserved for operator overloading
            "uncounted", // reserved to mark a struct/class as non ref-counted, better ABI match with c/c++.
            "weak", // lets the compiler know to not
        };

        int cur = '\0';
        std::size_t ln = 0;
        std::stack<tokenizer_state> state_stack;
        tokenizer_state state = tokenizer_state::DEFAULT;
        std::string scratch;
        std::size_t verbatim_depth = 0;

        std::vector<token> tokenstream;

        while (cur = filebuffer.peek(), !filebuffer.eof()) {
            if (cur == '\n')
                ln++;

            if (state == tokenizer_state::MLCOMMENT && cur == '*') {
                filebuffer.ignore();

                if (filebuffer.peek() == '/') { // end of multiline comment
                    tokenstream.emplace_back(token::COMMENT, token_comment{scratch});
                    state = tokenizer_state::DEFAULT;
                    continue;
                }

                filebuffer.unget();
            }

            if (state == tokenizer_state::PRE_VERBATIM && cur == '{') {
                filebuffer.ignore();
                state = tokenizer_state::VERBATIM;
                scratch.clear();
                continue;
            }

            // TODO: verbatim blocks will eat `}` in comments!
            if (state == tokenizer_state::VERBATIM) {
                if (cur == '}' && verbatim_depth == 0) {
                    filebuffer.ignore();
                    state = tokenizer_state::DEFAULT;
                    tokenstream.emplace_back(token::VERBATIM, token_verbatim{scratch});
                    continue;
                }
                if (cur == '{')
                    verbatim_depth++;
                if (cur == '}')
                    verbatim_depth--;
                scratch += filebuffer.get();
                continue;
            }

            if (state == tokenizer_state::IDENT) {
                if (std::isalnum(cur)) {
                    scratch += filebuffer.get();
                    continue;
                } else {
                    if (scratch == "verbatim") {
                        // special token
                        state = tokenizer_state::PRE_VERBATIM;
                        continue;
                    }
                    else if (keywords.contains(scratch))
                        tokenstream.emplace_back(token::KEYWORD, token_keyword{scratch});
                    else
                        tokenstream.emplace_back(token::IDENT, token_ident{scratch});
                    state = tokenizer_state::DEFAULT;
                }
            }

            if (state == tokenizer_state::NUM) {
                if (std::isalnum(cur)) {
                    scratch += filebuffer.get();
                    continue;
                } else {

                }
            }

            if (cur == '\n') {
                if (state == tokenizer_state::SLCOMMENT) {
                    tokenstream.emplace_back(token::COMMENT, token_comment{scratch});
                    state = tokenizer_state::DEFAULT;
                }
                // inject newline into the stream, only used for debug purposes.
                tokenstream.emplace_back(token::LINECOUNT, token_line{ln - 1});
                filebuffer.ignore();
                continue;
            }

            if (state == tokenizer_state::MLCOMMENT || state == tokenizer_state::SLCOMMENT) {
                scratch += filebuffer.get();
                continue;
            }

            if (state == tokenizer_state::ESCAPED) {
                scratch += filebuffer.get();
                state = state_stack.top();
                state_stack.pop();
                continue;
            }

            if (cur == '"') {
                filebuffer.ignore();
                if (state == tokenizer_state::STRING) {
                    tokenstream.emplace_back(token::STRING, token_string {scratch});
                    continue;
                } else if (state == tokenizer_state::DEFAULT) {
                    state = tokenizer_state::STRING;
                    scratch.clear();
                    continue;
                } else
                    unreachable("state not STRING or DEFAULT when reached \"");
            }

            if (state == tokenizer_state::STRING) {
                scratch += filebuffer.get();
                if (cur == '\\') {
                    // escaped character
                    state_stack.push(state);
                    state = tokenizer_state::ESCAPED;
                }
                continue;
            }

            if (cur == '/') {
                filebuffer.ignore();
                if (filebuffer.peek() == '/') { // single line comment
                    filebuffer.ignore();
                    state = tokenizer_state::SLCOMMENT;
                    scratch.clear();
                    continue;
                } else if (filebuffer.peek() == '*') { // multi line comment
                    filebuffer.ignore();
                    state = tokenizer_state::MLCOMMENT;
                    scratch.clear();
                    continue;
                }
                filebuffer.unget();
            }

            if (std::isalpha(cur)) {
                // begin ident or keyword
                state = tokenizer_state::IDENT;
                scratch.clear();
                scratch += cur;
                filebuffer.ignore();
                continue;
            }

            if (std::isdigit(cur)) {
                // this is a number
                state = tokenizer_state::NUM;
                scratch.clear();
                continue;
            }

            if (std::isspace(cur)) { // handle whitespace
                while (std::isspace(filebuffer.peek()))
                    filebuffer.ignore();

                tokenstream.emplace_back(token::WS, std::monostate{});
            }
        }

        return tokenstream;
    }

    void parser::load(const driver::compile_context &ctx) {
        std::fstream file(ctx.main_file);

        filebuffer << file.rdbuf();

        file.close();
    }
}
