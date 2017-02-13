#include <catch.hpp>

#include <algorithm>

// Catch defines a FAIL macro which interferes with the SQL FAIL syntax below.
// FAIL will be undefined for this file as it is unused.
#undef FAIL

#include "sqlite3pp/query.hxx"

namespace {
    using namespace sqlite3pp;

    template <class Name, class Age>
    struct person_table {
        Name name;
        Age age;
    };

    static constexpr auto age = column("age");
    static constexpr auto name = column("name");

    constexpr auto person = table<person_table>("person", name, age);
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

TEST_CASE("UPDATE table syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE(person).to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE person"));
}

//

TEST_CASE("UPDATE OR ROLLBACK table syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.ROLLBACK(person).to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR ROLLBACK person"));
}

TEST_CASE("UPDATE OR ABORT table syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.ABORT(person).to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR ABORT person"));
}

TEST_CASE("UPDATE OR REPLACE table syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.REPLACE(person).to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR REPLACE person"));
}

TEST_CASE("UPDATE OR FAIL table syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.FAIL(person).to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR FAIL person"));
}

TEST_CASE("UPDATE OR IGNORE table syntax works", "[test-update-statement]") {
    constexpr auto update_str = UPDATE.OR.IGNORE(person).to_str();

    REQUIRE(std::equal(update_str.begin(), update_str.end(), "UPDATE OR IGNORE person"));
}
