#include "catch.hpp"

#include "sqlitepp/sqlite3/error.hxx"


namespace {
    using namespace sqlitepp::sqlite3;
}

// IOERR tests
TEST_CASE("is_io_error returns true for IOERR", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR));
}

TEST_CASE("is_io_error returns true for IOERR_READ", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_READ));
}

TEST_CASE("is_io_error returns true for IOERR_SHORT_READ", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_SHORT_READ));
}

TEST_CASE("is_io_error returns true for IOERR_WRITE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_WRITE));
}

TEST_CASE("is_io_error returns true for IOERR_FSYNC", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_FSYNC));
}

TEST_CASE("is_io_error returns true for IOERR_DIR_FSYNC", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_DIR_FSYNC));
}

TEST_CASE("is_io_error returns true for IOERR_TRUNCATE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_TRUNCATE));
}

TEST_CASE("is_io_error returns true for IOERR_FSTAT", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_FSTAT));
}

TEST_CASE("is_io_error returns true for IOERR_UNLOCK", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_UNLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_RDLOCK", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_RDLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_DELETE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_DELETE));
}

TEST_CASE("is_io_error returns true for IOERR_BLOCKED", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_BLOCKED));
}

TEST_CASE("is_io_error returns true for IOERR_NOMEM", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_NOMEM));
}

TEST_CASE("is_io_error returns true for IOERR_ACCESS", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_ACCESS));
}

TEST_CASE("is_io_error returns true for IOERR_CHECKRESERVEDLOCK", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_CHECKRESERVEDLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_LOCK", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_LOCK));
}

TEST_CASE("is_io_error returns true for IOERR_CLOSE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_CLOSE));
}

TEST_CASE("is_io_error returns true for IOERR_DIR_CLOSE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_DIR_CLOSE));
}

TEST_CASE("is_io_error returns true for IOERR_SHMOPEN", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_SHMOPEN));
}

TEST_CASE("is_io_error returns true for IOERR_SHMSIZE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_SHMSIZE));
}

TEST_CASE("is_io_error returns true for IOERR_SHMLOCK", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_SHMLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_SHMMAP", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_SHMMAP));
}

TEST_CASE("is_io_error returns true for IOERR_SEEK", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_SEEK));
}

TEST_CASE("is_io_error returns true for IOERR_DELETE_NOENT", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_DELETE_NOENT));
}

TEST_CASE("is_io_error returns true for IOERR_MMAP", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_MMAP));
}


TEST_CASE("is_io_error returns true for IOERR_GETTEMPPATH", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_GETTEMPPATH));
}

TEST_CASE("is_io_error returns true for IOERR_CONVPATH", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_CONVPATH));
}

TEST_CASE("is_io_error returns true for IOERR_VNODE", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_VNODE));
}

TEST_CASE("is_io_error returns true for IOERR_AUTH", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_AUTH));
}

// LOCKED tests
TEST_CASE("is_locked_error returns true for LOCKED", "[test-sqlite3-error]") {
    REQUIRE(is_locked_error(error::LOCKED));
}

TEST_CASE("is_locked_error returns true for LOCKED_SHAREDCACHE", "[test-sqlite3-error]") {
    REQUIRE(is_locked_error(error::LOCKED_SHAREDCACHE));
}

// BUSY tests
TEST_CASE("is_busy_error returns true for BUSY", "[test-sqlite3-error]") {
    REQUIRE(is_busy_error(error::BUSY));
}

TEST_CASE("is_busy_error returns true for BUSY_RECOVERY", "[test-sqlite3-error]") {
    REQUIRE(is_busy_error(error::BUSY_RECOVERY));
}

TEST_CASE("is_busy_error returns true for BUSY_SNAPSHOT", "[test-sqlite3-error]") {
    REQUIRE(is_busy_error(error::BUSY_SNAPSHOT));
}

// CANT_OPEN tests
TEST_CASE("is_cant_open_error returns true for CANTOPEN", "[test-sqlite3-error]") {
    REQUIRE(is_cant_open_error(error::CANTOPEN));
}

TEST_CASE("is_cant_open_error returns true for CANTOPEN_NOTEMPTDIR", "[test-sqlite3-error]") {
    REQUIRE(is_cant_open_error(error::CANTOPEN_NOTEMPDIR));
}

TEST_CASE("is_cant_open_error returns true for CANTOPEN_ISDIR", "[test-sqlite3-error]") {
    REQUIRE(is_cant_open_error(error::CANTOPEN_ISDIR));
}

TEST_CASE("is_cant_open_error returns true for CANTOPEN_FULLPATH", "[test-sqlite3-error]") {
    REQUIRE(is_cant_open_error(error::CANTOPEN_FULLPATH));
}

TEST_CASE("is_cant_open_error returns true for CANTOPEN_CONVPATH", "[test-sqlite3-error]") {
    REQUIRE(is_cant_open_error(error::CANTOPEN_CONVPATH));
}

// CORRUPT tests
TEST_CASE("is_corrupt_error returns true for CORRUPT", "[test-sqlite3-error]") {
    REQUIRE(is_corrupt_error(error::CORRUPT));
}

TEST_CASE("is_corrupt_error returns true for CORRUPT_VTAB", "[test-sqlite3-error]") {
    REQUIRE(is_corrupt_error(error::CORRUPT_VTAB));
}

// READONLY tests
TEST_CASE("is_readonly_error returns true for READONLY", "[test-sqlite3-error]") {
    REQUIRE(is_readonly_error(error::READONLY));
}

TEST_CASE("is_readonly_error returns true for READONLY_RECOVERY", "[test-sqlite3-error]") {
    REQUIRE(is_readonly_error(error::READONLY_RECOVERY));
}

TEST_CASE("is_readonly_error returns true for READONLY_CANTLOCK", "[test-sqlite3-error]") {
    REQUIRE(is_readonly_error(error::READONLY_CANTLOCK));
}

TEST_CASE("is_readonly_error returns true for READONLY_ROLLBACK", "[test-sqlite3-error]") {
    REQUIRE(is_readonly_error(error::READONLY_ROLLBACK));
}

TEST_CASE("is_readonly_error returns true for READONLY_DBMOVED", "[test-sqlite3-error]") {
    REQUIRE(is_readonly_error(error::READONLY_DBMOVED));
}

// ABORT tests
TEST_CASE("is_abort_error returns true for ABORT", "[test-sqlite3-error]") {
    REQUIRE(is_abort_error(error::ABORT));
}

TEST_CASE("is_abort_error returns true for ABORT_ROLLBACK", "[test-sqlite3-error]") {
    REQUIRE(is_abort_error(error::ABORT_ROLLBACK));
}

// CONSTRAINT tests
TEST_CASE("is_constraint_error returns true for CONSTRAINT", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_CHECK", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_CHECK));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_COMMITHOOK", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_COMMITHOOK));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_FOREIGNKEY", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_FOREIGNKEY));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_FUNCTION", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_FUNCTION));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_NOTNULL", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_NOTNULL));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_PRIMARYKEY", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_PRIMARYKEY));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_TRIGGER", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_TRIGGER));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_UNIQUE", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_UNIQUE));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_VTAB", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_VTAB));
}

TEST_CASE("is_constraint_error returns true for CONSTRAINT_ROWID", "[test-sqlite3-error]") {
    REQUIRE(is_constraint_error(error::CONSTRAINT_ROWID));
}

// NOTICE tests
TEST_CASE("is_notice_error returns true for NOTICE", "[test-sqlite3-error]") {
    REQUIRE(is_notice_error(error::NOTICE));
}

TEST_CASE("is_notice_error returns true for NOTICE_RECOVER_WAL", "[test-sqlite3-error]") {
    REQUIRE(is_notice_error(error::NOTICE_RECOVER_WAL));
}

TEST_CASE("is_notice_error returns true for NOTICE_RECOVER_ROLLBACK", "[test-sqlite3-error]") {
    REQUIRE(is_notice_error(error::NOTICE_RECOVER_ROLLBACK));
}

// WARNING tests
TEST_CASE("is_warning_error returns true for WARNING", "[test-sqlite3-error]") {
    REQUIRE(is_warning_error(error::WARNING));
}

TEST_CASE("is_warning_error returns true for WARNING_AUTOINDEX", "[test-sqlite3-error]") {
    REQUIRE(is_warning_error(error::WARNING_AUTOINDEX));
}

// AUTH tests
TEST_CASE("is_auth_error returns true for AUTH", "[test-sqlite3-error]") {
    REQUIRE(is_auth_error(error::AUTH));
}

TEST_CASE("is_auth_error returns true for AUTH_USER", "[test-sqlite3-error]") {
    REQUIRE(is_auth_error(error::AUTH_USER));
}

// OK tests
TEST_CASE("is_ok returns true for OK", "[test-sqlite3-error]") {
    REQUIRE(is_ok(error::OK));
}

TEST_CASE("is_ok returns true for OK_LOAD_PERMANENTLY", "[test-sqlite3-error]") {
    REQUIRE(is_ok(error::OK_LOAD_PERMANENTLY));
}
