cmake_minimum_required(VERSION 3.8)

set(PROJECT tqml)
set(LIBRARIES
    interpreter
    filesystem
    parserlib
    termlib)
set(SOURCES ../src/main.cpp)

project(${PROJECT})

include_directories(../src)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

foreach (LIBRARY ${LIBRARIES})
    add_subdirectory(../src/${LIBRARY}/bin bin/${LIBRARY})
endforeach ()

add_executable(${PROJECT} ${SOURCES})

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT} ${LIBRARIES} ${CURSES_LIBRARIES})

