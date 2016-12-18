#include <catch.hpp>
#include <algorithm>

#include "sqlite3pp/query.hxx"


namespace {
    using namespace sqlite3pp;

    static constexpr auto name = column("name");
    static constexpr auto age = column("age");
    static constexpr auto gender = column("gender");
}


TEST_CASE("columns are serializable.", "test-sql-column") {
    constexpr auto name_str = name.to_str();

    REQUIRE(std::equal(name_str.begin(), name_str.end(), "name"));
}


TEST_CASE("Single column can be used with the = operator and a literal expression", "[test-sql-column]") {
    constexpr auto column_str = (name = I(2345)).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "name=2345"));
}

TEST_CASE("Single column can be used with the = operator and a column", "[test-sql-column]") {
    constexpr auto column_str = (name = age).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "name=age"));
}

TEST_CASE("Columns can be used to create a comma separated column list with literal expression", "[test-sql-column]") {
    constexpr auto column_str = ((name, age) = I(100)).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(name,age)=100"));
}

TEST_CASE("Columns can be used to create a comma separated column list with column", "[test-sql-column]") {
    constexpr auto column_str = ((name, age) = gender).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(name,age)=gender"));
}

TEST_CASE("Three columns can be used to create a comma separated column list with three elements", "[test-sql-column]") {
    constexpr auto column_str = (age, name, gender).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(age,name,gender)"));
}

TEST_CASE("Three columns can be used to create a comma separated column list with a literal expression", "[test-sql-column]") {
    constexpr auto column_str = ((age, name, gender)=S("world")).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(age,name,gender)='world'"));
}

TEST_CASE("Three columns can be used to create a comma separated column list with a column", "[test-sql-column]") {
    constexpr auto column_str = ((age, name, gender)=gender).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(age,name,gender)=gender"));
}
