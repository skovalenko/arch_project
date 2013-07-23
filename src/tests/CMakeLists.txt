cmake_minimum_required(VERSION 2.8)

set(PROJECT tests)

project(${PROJECT})

set(HEADERS
    test_file.h
    test_freq_processor.h)

set(SOURCES
    tests.cpp
    ../file.cpp
    ../frequency_processor.cpp)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT} pthread gtest)
