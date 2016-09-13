cmake_minimum_required(VERSION 3.5)
project(sqlitepp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SQLITEPP_SOURCE_FILES
        #sqlitepp
        sqlitepp/sql/sql_strings.hxx

        # sqlite3
        sqlitepp/sqlite3/prepared_statement.cxx
        sqlitepp/sqlite3/connection.cxx
        sqlitepp/sqlite3/error.cxx
)
add_library(sqlitepp ${SQLITEPP_SOURCE_FILES})
target_link_libraries(sqlitepp
        sqlite3
)
set_property(TARGET sqlitepp PROPERTY CXX_STANDARD 14)
target_include_directories(sqlitepp PUBLIC
        ${CMAKE_SOURCE_DIR}  # TODO: Change this to the include directory once that refactoring is done.
)

add_subdirectory(tests)
target_include_directories(sqlitepp_tests PUBLIC
        Catch/single_include
)
set_property(TARGET sqlitepp_tests PROPERTY CXX_STANDARD 14)