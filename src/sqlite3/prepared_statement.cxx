#include "sqlite3pp/sqlite3/prepared_statement.hxx"

#include <limits>


auto sqlite3pp::sqlite3::make_prepared_statement(connection & conn, const sql::str &sql_str) -> expected<prepared_statement>  {
    sqlite3_stmt *prepared_statement_ptr;

    if (sql_str.length() > std::numeric_limits<int>::max()) {
        return {error::TOOBIG};
    }

    auto err = static_cast<error>(sqlite3_prepare_v2(conn, sql_str.c_str(), static_cast<int>(sql_str.length()), &prepared_statement_ptr, nullptr));

    if (err != error::OK) {
        return {err};
    }

    return {{prepared_statement_ptr}};
}

auto sqlite3pp::sqlite3::make_prepared_statement_v1(connection &conn, const sql::str &sql_str) -> expected<prepared_statement> {
    sqlite3_stmt *prepared_statement_ptr;

    if (sql_str.length() > std::numeric_limits<int>::max()) {
        return {error::TOOBIG};
    }

    auto err = static_cast<error>(sqlite3_prepare(conn, sql_str.c_str(), static_cast<int>(sql_str.length()), &prepared_statement_ptr, nullptr));

    if (err != error::OK) {
        return {err};
    }

    return {{prepared_statement_ptr}};
}
