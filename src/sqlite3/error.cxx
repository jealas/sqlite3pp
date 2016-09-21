#include "sqlite3pp/sqlite3/error.hxx"

#include <type_traits>


bool sqlite3pp::sqlite3::is_io_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_IOERR;
}

bool sqlite3pp::sqlite3::is_locked_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_LOCKED;
}

bool sqlite3pp::sqlite3::is_busy_error(error err)  {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_BUSY;
}

bool sqlite3pp::sqlite3::is_cant_open_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_CANTOPEN;
}

bool sqlite3pp::sqlite3::is_corrupt_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_CORRUPT;
}

bool sqlite3pp::sqlite3::is_readonly_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_READONLY;
}

bool sqlite3pp::sqlite3::is_abort_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_ABORT;
}

bool sqlite3pp::sqlite3::is_constraint_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_CONSTRAINT;
}

bool sqlite3pp::sqlite3::is_notice_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_NOTICE;
}

bool sqlite3pp::sqlite3::is_warning_error(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_WARNING;
}

bool sqlite3pp::sqlite3::is_auth_error(error err) {
    int a = static_cast<int>(err);
    int aa = a & 0xFF;
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_AUTH;
}

bool sqlite3pp::sqlite3::is_ok(error err) {
    return (static_cast<std::underlying_type_t<error>>(err) & 0xFF) == SQLITE_OK;
}
