#include "catch.hpp"

#include "sqlitepp/sqlite3/error.hxx"


namespace {
    using namespace sqlitepp::sqlite3;
}


TEST_CASE("is_io_error returns true for IOERR", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR));
}

TEST_CASE("is_io_error returns true for IOERR_READ", "[test-sqlite3-error]") {
    REQUIRE(is_io_error(error::IOERR_READ));
}

TEST_CASE("is_io_error returns true for IOERR_SHORT_READ") {
    REQUIRE(is_io_error(error::IOERR_SHORT_READ));
}

TEST_CASE("is_io_error returns true for IOERR_WRITE") {
    REQUIRE(is_io_error(error::IOERR_WRITE));
}

TEST_CASE("is_io_error returns true for IOERR_FSYNC") {
    REQUIRE(is_io_error(error::IOERR_FSYNC));
}

TEST_CASE("is_io_error returns true for IOERR_DIR_FSYNC") {
    REQUIRE(is_io_error(error::IOERR_DIR_FSYNC));
}

TEST_CASE("is_io_error returns true for IOERR_TRUNCATE") {
    REQUIRE(is_io_error(error::IOERR_TRUNCATE));
}

TEST_CASE("is_io_error returns true for IOERR_FSTAT") {
    REQUIRE(is_io_error(error::IOERR_FSTAT));
}

TEST_CASE("is_io_error returns true for IOERR_UNLOCK") {
    REQUIRE(is_io_error(error::IOERR_UNLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_RDLOCK") {
    REQUIRE(is_io_error(error::IOERR_RDLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_DELETE") {
    REQUIRE(is_io_error(error::IOERR_DELETE));
}

TEST_CASE("is_io_error returns true for IOERR_BLOCKED") {
    REQUIRE(is_io_error(error::IOERR_BLOCKED));
}

TEST_CASE("is_io_error returns true for IOERR_NOMEM") {
    REQUIRE(is_io_error(error::IOERR_NOMEM));
}

TEST_CASE("is_io_error returns true for IOERR_ACCESS") {
    REQUIRE(is_io_error(error::IOERR_ACCESS));
}

TEST_CASE("is_io_error returns true for IOERR_CHECKRESERVEDLOCK") {
    REQUIRE(is_io_error(error::IOERR_CHECKRESERVEDLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_LOCK") {
    REQUIRE(is_io_error(error::IOERR_LOCK));
}

TEST_CASE("is_io_error returns true for IOERR_CLOSE") {
    REQUIRE(is_io_error(error::IOERR_CLOSE));
}

TEST_CASE("is_io_error returns true for IOERR_DIR_CLOSE") {
    REQUIRE(is_io_error(error::IOERR_DIR_CLOSE));
}

TEST_CASE("is_io_error returns true for IOERR_SHMOPEN") {
    REQUIRE(is_io_error(error::IOERR_SHMOPEN));
}

TEST_CASE("is_io_error returns true for IOERR_SHMSIZE") {
    REQUIRE(is_io_error(error::IOERR_SHMSIZE));
}

TEST_CASE("is_io_error returns true for IOERR_SHMLOCK") {
    REQUIRE(is_io_error(error::IOERR_SHMLOCK));
}

TEST_CASE("is_io_error returns true for IOERR_SHMMAP") {
    REQUIRE(is_io_error(error::IOERR_SHMMAP));
}

TEST_CASE("is_io_error returns true for IOERR_SEEK") {
    REQUIRE(is_io_error(error::IOERR_SEEK));
}

TEST_CASE("is_io_error returns true for IOERR_DELETE_NOENT") {
    REQUIRE(is_io_error(error::IOERR_DELETE_NOENT));
}

TEST_CASE("is_io_error returns true for IOERR_MMAP") {
    REQUIRE(is_io_error(error::IOERR_MMAP));
}


TEST_CASE("is_io_error returns true for IOERR_GETTEMPPATH") {
    REQUIRE(is_io_error(error::IOERR_GETTEMPPATH));
}

TEST_CASE("is_io_error returns true for IOERR_CONVPATH") {
    REQUIRE(is_io_error(error::IOERR_CONVPATH));
}

TEST_CASE("is_io_error returns true for IOERR_VNODE") {
    REQUIRE(is_io_error(error::IOERR_VNODE));
}

TEST_CASE("is_io_error returns true for IOERR_AUTH") {
    REQUIRE(is_io_error(error::IOERR_AUTH));
}
