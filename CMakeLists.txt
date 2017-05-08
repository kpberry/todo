cmake_minimum_required(VERSION 3.6)
project(todo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/task.cpp src/main.cpp src/project.cpp src/project.hpp src/main.hpp src/date/scanner.cpp src/date/scanner.hpp src/date/token.cpp src/date/token.hpp)
add_executable(todo ${SOURCE_FILES})