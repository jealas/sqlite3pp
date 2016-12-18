cmake_minimum_required(VERSION 3.5)
project(sqlite3pp CXX)

set(SQLITE3PP_SOURCE_FILES
        # sqlite3
        src/sqlite3/prepared_statement.cxx
        src/sqlite3/connection.cxx
        src/sqlite3/error.cxx
        src/sqlite3/progress_handler.cxx
        include/sqlite3pp/sql/insert_statement.hxx include/sqlite3pp/sql/update_statement.hxx)

add_library(sqlite3pp SHARED ${SQLITE3PP_SOURCE_FILES})

target_link_libraries(sqlite3pp
        sqlite3
)

set_property(TARGET sqlite3pp PROPERTY CXX_STANDARD 14)

target_include_directories(sqlite3pp PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(tests)
