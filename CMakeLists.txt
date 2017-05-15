cmake_minimum_required(VERSION 3.5)
project(todo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/task.cpp
        src/main.cpp
        src/project.cpp
        src/project.hpp
        src/main.hpp
        src/date/scanner.cpp
        src/date/scanner.hpp
        src/date/token.cpp
        src/date/token.hpp
        src/text/string_formatter.cpp
        src/text/string_formatter.hpp
        src/text/color.hpp
        src/text/color.cpp src/view/terminal/view.cpp src/view/terminal/view.hpp src/view/gui/gui.cpp src/view/gui/gui.hpp)
add_executable(todo ${SOURCE_FILES})
