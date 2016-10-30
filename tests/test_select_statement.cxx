#include <catch.hpp>
#include <algorithm>

#include "sqlite3pp/query.hxx"

namespace {

    using namespace sqlite3pp;

    template <class T>
    struct name_column_member {
        T name;
    };

    static constexpr auto name = column<name_column_member, column_type::TEXT>("name");

    template <class T>
    struct age_column_member {
        T age;
    };

    static constexpr auto age = column<age_column_member, column_type::INTEGER>("age");

    static constexpr auto person = table("person", age, name);
}

TEST_CASE("Can use SELECT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name"));
}

TEST_CASE("Can use SELECT statement with expressions.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(I(1), F(3.14)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT 1,3.14"));
}

TEST_CASE("Can use SELECT ALL statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.ALL(age, name).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT ALL age,name"));
}

TEST_CASE("Can use SELECT ALL statement with expressions.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.ALL(I(1), F(3.14)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT ALL 1,3.14"));
}

TEST_CASE("Can use SELECT DISTINCT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.DISTINCT(age, name).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT DISTINCT age,name"));
}

TEST_CASE("Can use SELECT DISTINCT statement with expressions.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.DISTINCT(I(1), F(3.14)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT DISTINCT 1,3.14"));
}

TEST_CASE("Can use SELECT FROM statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name).FROM(person).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person"));
}

TEST_CASE("Can use SELECT ALL FROM statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.ALL(age, name).FROM(person).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT ALL age,name FROM person"));
}

TEST_CASE("Can use SELECT DISTINCT FROM statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.DISTINCT(age, name).FROM(person).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT DISTINCT age,name FROM person"));
}

TEST_CASE("Can use SELECT FROM WHERE statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name).FROM(person).WHERE(age == I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age==10"));
}

TEST_CASE("Can use SELECT ALL FROM WHERE statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.ALL(age, name).FROM(person).WHERE(name != S("joe")).to_str();


    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT ALL age,name FROM person WHERE name!='joe'"));
}

TEST_CASE("Can use SELECT DISTINCT FROM WHERE statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.DISTINCT(age, name).FROM(person).WHERE((age < I(20)).AND(name != S("tom"))).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT DISTINCT age,name FROM person WHERE age<20 AND name!='tom'"));
}
