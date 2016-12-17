#include <catch.hpp>
#include <algorithm>

#include "sqlite3pp/query.hxx"


namespace {
    using namespace sqlite3pp;

    static constexpr auto name_column = column("name");
    static constexpr auto age_column = column("age");
    static constexpr auto gender_column = column("gender");
}


TEST_CASE("columns are serializable.", "test-sql-column") {
    constexpr auto name_str = name_column.to_str();

    REQUIRE(std::equal(name_str.begin(), name_str.end(), "name"));
}


TEST_CASE("Single column can be used with the = operator and a literal expression", "[test-sql-column]") {
    constexpr auto column_str = (name_column = I(2345)).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "name=2345"));
}

TEST_CASE("Single column can be used with the = operator and a column", "[test-sql-column]") {
    constexpr auto column_str = (name_column = age_column).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "name=age"));
}

TEST_CASE("Columns can be used to create a comma separated column list with literal expression", "[test-sql-column]") {
    constexpr auto column_str = ((name_column, age_column) = I(100)).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(name,age)=100"));
}

TEST_CASE("Columns can be used to create a comma separated column list with column", "[test-sql-column]") {
    constexpr auto column_str = ((name_column, age_column) = gender_column).to_str();

    REQUIRE(std::equal(column_str.begin(), column_str.end(), "(name,age)=gender"));
}

TEST_CASE("Three columns can be used to create a comma separated column list with a literal expression") {
//    constexpr auto column_str = (age_column, name_column, gender_column).to_str();
}
