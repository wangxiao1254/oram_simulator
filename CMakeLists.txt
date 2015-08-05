project(log3oram)
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "-O3 --std=c++0x -DNDEBUG -Wall -Wno-sign-compare")
#set(CMAKE_CXX_FLAGS "-g -ggdb --std=c++0x -Wall")

include_directories(${CMAKE_SOURCE_DIR})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

add_executable(path_oram
    path_oram/test.cpp
)

add_executable(path_oram_determinstic
    path_oram_deterministic/test.cpp
)

add_executable(circuit_oram
    circuit_oram/test.cpp
)

add_executable(circuit_oram_determinstic
    circuit_oram_deterministic/test.cpp
)
