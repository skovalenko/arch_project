cmake_minimum_required(VERSION 2.8)

set(PROJECT arch)

project(${PROJECT})

set(HEADERS
    src/file.h
    src/frequency_processor.h
    src/tree.h
    src/archivator_manager.h)

set(SOURCES
    src/main.cpp
    src/file.cpp
    src/frequency_processor.cpp
    src/tree.cpp
    src/archivator_manager.cpp)

include_directories(src)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})

add_subdirectory(src/tests)
