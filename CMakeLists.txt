cmake_minimum_required(VERSION 3.30)
project(dwlang)

set(CMAKE_CXX_STANDARD 26)

add_executable(dcc
# driver code
        src/driver/main.cpp
        src/driver/compile_context.cpp
        src/driver/compile_context.h
        src/frontend/parser/parser.cpp
        src/frontend/parser/parser.h
        src/frontend/parser/token.h
        src/frontend/parser/token.cpp
        src/common/utilities.h
)
target_include_directories(dcc PRIVATE src)
