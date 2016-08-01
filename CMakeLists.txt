cmake_minimum_required(VERSION 3.5)
project(sqlitepp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE_FILES main.cpp sqlitepp/sql/sql_strings.hxx)
add_executable(sqlitepp ${SOURCE_FILES})