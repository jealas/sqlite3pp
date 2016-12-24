#include <catch.hpp>

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


TEST_CASE("Can use CREATE statement", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE"));
}

TEST_CASE("Can use CREATE TEMP statement", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TEMP.to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TEMP"));
}

TEST_CASE("Can use CREATE TEMPORARY statement", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TEMPORARY.to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TEMPORARY"));
}

TEST_CASE("Can use CREATE TABLE statement", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TABLE.to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TABLE"));
}

TEST_CASE("Can use CREATE TEMP TABLE statement", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TEMP.TABLE.to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TEMP TABLE"));
}

TEST_CASE("Can use CREATE TEMPORARY TABLE statement", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TEMPORARY.TABLE.to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TEMPORARY TABLE"));
}

TEST_CASE("Can use CREATE TABLE statement with table name", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TABLE(person).to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TABLE person"));
}

TEST_CASE("Can use CREATE TEMP TABLE statement with table name", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TEMP.TABLE(person).to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TEMP TABLE person"));
}

TEST_CASE("Can use CREATE TEMPORARY TABLE statement with table name", "[test-create-table-statement]") {
    constexpr auto create_str = CREATE.TEMPORARY.TABLE(person).to_str();

    REQUIRE(std::equal(create_str.begin(), create_str.end(), "CREATE TEMPORARY TABLE person"));
}
