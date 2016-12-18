add_executable(sqlite3pp_tests
        sqlite3pp_tests_main.cxx

        # sqlite3pp
        test_sqlite3_error.cxx

        # sql
        test_sql_column.cxx
        test_sql_expressions.cxx
        test_select_statement.cxx
        test_insert_statement.cxx test_update_statement.cxx)

target_link_libraries(sqlite3pp_tests
        sqlite3pp
)

set_property(TARGET sqlite3pp_tests PROPERTY CXX_STANDARD 14)

target_include_directories(sqlite3pp_tests PUBLIC
        ${CMAKE_SOURCE_DIR}/Catch/single_include
)
