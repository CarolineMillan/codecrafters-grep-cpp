cmake_minimum_required(VERSION 3.13)

project(grep-starter-cpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

add_executable(exe ${SOURCE_FILES}
        src/nfa_fragment.h
        src/main.cpp
        src/parser.h
        src/parser.cpp
        src/compiler.h
        src/compiler.cpp
)