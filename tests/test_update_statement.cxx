#include <catch.hpp>

#include <algorithm>

#include "sqlite3pp/query.hxx"

namespace {
    using namespace sqlite3pp;
}


TEST_CASE("UPDATE syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE"));
}

TEST_CASE("UPDATE OR syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR"));
}

TEST_CASE("UPDATE OR ROLLBACK syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.ROLLBACK.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR ROLLBACK"));
}

TEST_CASE("UPDATE OR ABORT syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.ABORT.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR ABORT"));
}

TEST_CASE("UPDATE OR REPLACE syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.REPLACE.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR REPLACE"));
}

TEST_CASE("UPDATE OR FAIL syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.FAIL.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR FAIL"));
}

TEST_CASE("UPDATE OR IGNORE syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.IGNORE.to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR IGNORE"));
}
