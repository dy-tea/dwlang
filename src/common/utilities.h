#pragma once

#include <iostream>

namespace ice {
    [[noreturn]] inline void unreachable(const std::string &msg = "") {
        std::cerr << "[FATAL] [ICE] Compiler reached unreachable statement, " << (msg.empty() ? "no error message" : msg) << std::endl;
        std::terminate();
    }
}
