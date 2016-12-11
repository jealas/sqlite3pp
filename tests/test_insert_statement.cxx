#include <catch.hpp>

#include <algorithm>

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

///###

TEST_CASE("Can use INSERT INTO person (name) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.INTO(person)(name).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT INTO person (name)"));
}

TEST_CASE("Can use INSERT INTO person (name,age) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.INTO(person)(age, name).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT INTO person (age,name)"));
}

TEST_CASE("Can use INSERT OR ROLLBACK INTO person statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ROLLBACK.INTO(person).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ROLLBACK INTO person"));
}

TEST_CASE("Can use INSERT OR ROLLBACK INTO person (name,age) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ROLLBACK.INTO(person)(name,age).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ROLLBACK INTO person (name,age)"));
}

TEST_CASE("Can use INSERT OR ABORT INTO person statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ABORT.INTO(person).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ABORT INTO person"));
}

TEST_CASE("Can use INSERT OR ABORT INTO person (name,age) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ABORT.INTO(person)(name,age).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ABORT INTO person (name,age)"));
}

TEST_CASE("Can use INSERT OR REPLACE INTO person statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.REPLACE.INTO(person).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR REPLACE INTO person"));
}

TEST_CASE("Can use INSERT OR REPLACE INTO person (name,age) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.REPLACE.INTO(person)(name,age).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR REPLACE INTO person (name,age)"));
}

TEST_CASE("Can use INSERT OR FAIL INTO person statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.FAIL.INTO(person).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR FAIL INTO person"));
}

TEST_CASE("Can use INSERT OR FAIL INTO person (name,age) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.FAIL.INTO(person)(name,age).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR FAIL INTO person (name,age)"));
}

TEST_CASE("Can use INSERT OR IGNORE INTO person statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.IGNORE.INTO(person).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR IGNORE INTO person"));
}

TEST_CASE("Can use INSERT OR IGNORE INTO person (name,age) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.IGNORE.INTO(person)(name,age).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR IGNORE INTO person (name,age)"));
}

//


TEST_CASE("Can use INSERT INTO person (name) VALUES ('bob') statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.INTO(person)(name).VALUES(S("bob")).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT INTO person (name) VALUES ('bob')"));
}

TEST_CASE("Can use INSERT INTO person (name, age) VALUES ('bob', 23) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.INTO(person)(name, age).VALUES(S("bob"), I(23)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT INTO person (name,age) VALUES ('bob',23)"));
}

TEST_CASE("Can use INSERT OR ROLLBACK INTO person VALUES ('tom', 24) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ROLLBACK.INTO(person).VALUES(S("tom"), I(24)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ROLLBACK INTO person VALUES ('tom',24)"));
}

TEST_CASE("Can use INSERT OR ROLLBACK INTO person name,age VALUES ('tom', 24) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ROLLBACK.INTO(person)(name,age).VALUES(S("tom"), I(24)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ROLLBACK INTO person (name,age) VALUES ('tom',24)"));
}

TEST_CASE("Can use INSERT OR ABORT INTO person VALUES ('moe',25) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ABORT.INTO(person).VALUES(S("moe"), I(25)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ABORT INTO person VALUES ('moe',25)"));
}

TEST_CASE("Can use INSERT OR ABORT INTO person name,age VALUES ('moe',25) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.ABORT.INTO(person)(name,age).VALUES(S("moe"), I(25)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR ABORT INTO person (name,age) VALUES ('moe',25)"));
}

TEST_CASE("Can use INSERT OR REPLACE INTO person VALUES ('moe',25) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.REPLACE.INTO(person).VALUES(S("moe"), I(25)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR REPLACE INTO person VALUES ('moe',25)"));
}

TEST_CASE("Can use INSERT OR REPLACE INTO person name,age VALUES ('moe',25) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.REPLACE.INTO(person)(name,age).VALUES(S("moe"), I(25)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR REPLACE INTO person (name,age) VALUES ('moe',25)"));
}

TEST_CASE("Can use INSERT OR FAIL INTO person VALUES ('john', 99) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.FAIL.INTO(person).VALUES(S("john"), I(99)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR FAIL INTO person VALUES ('john',99)"));
}

TEST_CASE("Can use INSERT OR FAIL INTO person name,age VALUES ('john',99) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.FAIL.INTO(person)(name,age).VALUES(S("john"), I(99)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR FAIL INTO person (name,age) VALUES ('john',99)"));
}

TEST_CASE("Can use INSERT OR IGNORE INTO person VALUES ('dwayne',100) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.IGNORE.INTO(person).VALUES(S("dwayne"), I(100)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR IGNORE INTO person VALUES ('dwayne',100)"));
}

TEST_CASE("Can use INSERT OR IGNORE INTO person name,age VALUES ('dwayne',100) statement", "[test-insert-statement]") {
    constexpr auto insert_str = INSERT.OR.IGNORE.INTO(person)(name,age).VALUES(S("dwayne"), I(100)).to_str();

    REQUIRE(std::equal(insert_str.begin(), insert_str.end(), "INSERT OR IGNORE INTO person (name,age) VALUES ('dwayne',100)"));
}
