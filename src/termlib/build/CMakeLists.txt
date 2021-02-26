cmake_minimum_required(VERSION 3.8)

set(PROJECT termlib)
set(SOURCES ../src/terminal.cpp ../src/term_windows.cpp)

include_directories(../include)

project(${PROJECT})

add_library(${PROJECT} STATIC ${SOURCES})

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


