#include "sqlitepp/sqlite3/error.hxx"

#include <type_traits>


bool sqlitepp::sqlite3::is_io_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_IOERR;
}

bool sqlitepp::sqlite3::is_locked_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_LOCKED;
}

bool sqlitepp::sqlite3::is_busy_error(error err)  {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_BUSY;
}

bool sqlitepp::sqlite3::is_cant_open_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_CANTOPEN;
}

bool sqlitepp::sqlite3::is_corrupt_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_CORRUPT;
}

bool sqlitepp::sqlite3::is_readonly_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_READONLY;
}

bool sqlitepp::sqlite3::is_abort_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_ABORT;
}

bool sqlitepp::sqlite3::is_constraint_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_CONSTRAINT;
}

bool sqlitepp::sqlite3::is_notice_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_NOTICE;
}

bool sqlitepp::sqlite3::is_warning_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_WARNING;
}

bool sqlitepp::sqlite3::is_auth_error(error err) {
    int a = static_cast<int>(err);
    int aa = a & 0xFF;
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_AUTH;
}

bool sqlitepp::sqlite3::is_ok(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_OK;
}
