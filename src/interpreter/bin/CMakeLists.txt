cmake_minimum_required(VERSION 3.8)

set(PROJECT interpreter)
set(HEADERS ../includes/interpreter.h)
set(SOURCES ../src/interpreter.cpp)

project(${PROJECT})

add_library(${PROJECT} STATIC ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
