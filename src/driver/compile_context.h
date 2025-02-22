#pragma once

#include <filesystem>

namespace driver {
    class compile_context {
    public:
        std::filesystem::path main_file;

        int compile();
    };
}
