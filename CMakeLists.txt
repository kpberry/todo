cmake_minimum_required(VERSION 3.6)
project(todo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES task.cpp main.cpp project.cpp project.hpp main.hpp date/scanner.cpp date/scanner.hpp date/token.cpp date/token.hpp)
add_executable(todo ${SOURCE_FILES})