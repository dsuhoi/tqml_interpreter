cmake_minimum_required(VERSION 3.8)

set(PROJECT termlib)
set(HEADERS ../terminal.h ../term_windows.h)
set(SOURCES ../sources/terminal.cpp ../sources/term_windows.cpp)

project(${PROJECT})

add_library(${PROJECT} STATIC ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


