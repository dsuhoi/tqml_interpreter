cmake_minimum_required(VERSION 3.8)

set(PROJECT interpreter)
set(HEADERS ../interpreter.h)
set(SOURCES ../sources/interpreter.cpp)

project(${PROJECT})

add_library(${PROJECT} STATIC ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
