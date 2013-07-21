cmake_minimum_required(VERSION 2.8)

set(PROJECT tests)

project(${PROJECT})

set(HEADERS
    test_file.h)

set(SOURCES
    tests.cpp
    ../file.cpp)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT} pthread gtest)
