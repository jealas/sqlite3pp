#include "sqlitepp/sqlite3/connection.hxx"

sqlitepp::sqlite3::connection::~connection() {
    close();
}

auto sqlitepp::sqlite3::connection::close() -> error {
    auto err = static_cast<error>(sqlite3_close_v2(connection_ptr));
    connection_ptr = nullptr;

    return err;
}

auto sqlitepp::sqlite3::make_connection(const char *filename, open_option options) -> expected<connection> {
    ::sqlite3 *connection_ptr = nullptr;

    auto err = static_cast<error>(sqlite3_open_v2(filename, &connection_ptr, options, nullptr));

    if (err != error::OK) {
        err = static_cast<error>(sqlite3_extended_errcode(connection_ptr));

        sqlite3_close_v2(connection_ptr);
        return {err};
    }

    return {{connection_ptr}};
}

auto sqlitepp::sqlite3::make_connection(const char *filename) -> expected<connection> {
    ::sqlite3 *connection_ptr = nullptr;

    auto err = static_cast<error>(sqlite3_open(filename, &connection_ptr));

    if (err != error::OK) {
        err = static_cast<error>(sqlite3_extended_errcode(connection_ptr));

        sqlite3_close(connection_ptr);
        return {err};
    }

    return {{connection_ptr}};
}