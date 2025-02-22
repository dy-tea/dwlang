#include <iostream>

#include "compile_context.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " source_files" << std::endl;
        std::cerr << "dcc: [fatal error]: no input files" << std::endl;
        return 1;
    }

    driver::compile_context context;

    context.main_file = argv[1];

    return context.compile();
}
