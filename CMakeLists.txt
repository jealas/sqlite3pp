cmake_minimum_required(VERSION 3.5)
project(sqlitepp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(sqlitepp ${SOURCE_FILES})

set_property(TARGET sqlitepp PROPERTY CXX_STANDARD 14)

add_subdirectory(tests)
target_include_directories(sqlitepp_tests PUBLIC
        Catch/single_include
)