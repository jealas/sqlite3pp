add_executable(sqlite3pp_tests
        sqlite3pp_tests_main.cxx
        test_sqlite3_error.cxx
)

target_link_libraries(sqlite3pp_tests
        sqlite3pp
)

set_property(TARGET sqlite3pp_tests PROPERTY CXX_STANDARD 14)

target_include_directories(sqlite3pp_tests PUBLIC
        ${CMAKE_SOURCE_DIR}/Catch/single_include
)
