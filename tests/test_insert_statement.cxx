#include <catch.hpp>

#include <algorithm>

#include "sqlite3pp/query.hxx"

namespace {
    using namespace sqlite3pp;
}

TEST_CASE("Can use INSERT INTO statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.INTO.to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT INTO"));
}

TEST_CASE("Can use INSERT OR ROLLBACK INTO statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ROLLBACK.INTO.to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ROLLBACK INTO"));
}

TEST_CASE("Can use INSERT OR ABORT INTO statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ABORT.INTO.to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ABORT INTO"));
}

TEST_CASE("Can use INSERT OR REPLACE INTO statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.REPLACE.INTO.to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR REPLACE INTO"));
}

TEST_CASE("Can use INSERT OR FAIL statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.FAIL.INTO.to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR FAIL INTO"));
}

TEST_CASE("Can use INSERT OR IGNORE statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.IGNORE.INTO.to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR IGNORE INTO"));
}
