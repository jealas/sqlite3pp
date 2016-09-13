add_executable(sqlitepp_tests
        sqlitepp_tests_main.cxx
        test_sqlite3_error.cxx
)

target_link_libraries(sqlitepp_tests
        sqlitepp
)