cmake_minimum_required(VERSION 3.8)

set(PROJECT parserlib)
set(HEADERS ../regex_parser.h ../text_data.h)
set(SOURCES ../sources/regex_parser.cpp ../sources/text_data.cpp)

project(${PROJECT})

add_library(${PROJECT} STATIC ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


