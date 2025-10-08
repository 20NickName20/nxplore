cmake_minimum_required(VERSION 3.10)
project(Nxplore VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Build executable
add_executable(Nxplore src/main.cpp)

# Link ncurses
target_link_libraries(Nxplore PRIVATE ${CURSES_LIBRARIES})
