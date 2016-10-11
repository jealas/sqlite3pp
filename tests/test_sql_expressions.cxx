#include <catch.hpp>
#include <algorithm>

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/literal_expressions.hxx"
#include "sqlite3pp/sql/column_type.hxx"
#include "sqlite3pp/sql/expressions.hxx"


namespace {

    using namespace sqlite3pp::sql;

    template <class T>
    struct name_column_member {
        T name;
    };

    constexpr auto name_column = column<name_column_member, column_type::TEXT>("name");

    template <class T>
    struct age_column_member {
        T age;
    };

    constexpr auto age_column = column<age_column_member, column_type::INTEGER>("age");
}


TEST_CASE("Columns can be used with the parenthesis function.", "[test-sql-expressions]") {
    constexpr auto parenthesis_column = P(age_column);
    constexpr auto parenthesis_column_str = parenthesis_column.to_str();

    REQUIRE(std::equal(parenthesis_column_str.begin(), parenthesis_column_str.end(), "(age)"));
}

TEST_CASE("Literal expressions can be used with the parenthesis function.") {
    constexpr auto parenthesis_literal_str = P(S("hello")).to_str();

    REQUIRE(std::equal(parenthesis_literal_str.begin(), parenthesis_literal_str.end(), "('hello')"));
}

TEST_CASE("Columns can be used with the || operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = age_column || name_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "age||name"));
}

TEST_CASE("Literal expressions can be used with the || operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(123) || F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "123||3.14"));
}

TEST_CASE("Columns can be used with the / operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column / age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name/age"));
}

TEST_CASE("Literal expressions can be used with the / operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = F(2.718) / F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718/3.14"));
}

TEST_CASE("Columns can be used with the % operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column % age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name%age"));
}

TEST_CASE("Literal expressions can be used with the % operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = F(2.718) % F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718%3.14"));
}

TEST_CASE("Columns can be used with the + operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column + age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name+age"));
}

TEST_CASE("Literal expressions can be used with the + operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = F(2.718) + F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718+3.14"));
}

TEST_CASE("Columns can be used with the - operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column - age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name-age"));
}

TEST_CASE("Literal expressions can be used with the - operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = F(2.718) - F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718-3.14"));
}

TEST_CASE("Columns can be used with the << operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column << age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name<<age"));
}

TEST_CASE("Literal expressions can be used with the << operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = F(2.718) << F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718<<3.14"));
}

TEST_CASE("Columns can be used with the >> operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column >> age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name>>age"));
}

TEST_CASE("Literal expressions can be used with the >> operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = F(2.718) >> F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718>>3.14"));
}

TEST_CASE("Columns can be used with the & operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column & age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name&age"));
}

TEST_CASE("Literal expressions can be used with the & operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) & I(3);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2&3"));
}

TEST_CASE("Columns can be used with the | operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column | age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name|age"));
}

TEST_CASE("Literal expressions can be used with the | operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) | I(3);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2|3"));
}

TEST_CASE("Columns can be used with the < operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column < age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name<age"));
}

TEST_CASE("Literal expressions can be used with the < operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) < F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2<3.14"));
}

TEST_CASE("Columns can be used with the > operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column > age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name>age"));
}

TEST_CASE("Literal expressions can be used with the > operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) > F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2>3.14"));
}

TEST_CASE("Columns can be used with the <= operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column <= age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name<=age"));
}

TEST_CASE("Literal expressions can be used with the <= operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) <= F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2<=3.14"));
}

TEST_CASE("Columns can be used with the >= operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column >= age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name>=age"));
}

TEST_CASE("Literal expressions can be used with the >= operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) >= F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2>=3.14"));
}

TEST_CASE("Columns can be used with the == operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column == age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name==age"));
}

TEST_CASE("Literal expressions can be used with the == operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) == F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2==3.14"));
}

TEST_CASE("Columns can be used with the != operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = name_column != age_column;
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name!=age"));
}

TEST_CASE("Literal expressions can be used with the != operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = I(2) != F(3.14);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2!=3.14"));
}

TEST_CASE("Columns can be used with the ~ operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression = ~age_column;
    constexpr auto expression_str = unary_expression.to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "~age"));
}

TEST_CASE("Literal expressions can be used with the ~ operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression = ~I(2);
    constexpr auto expression_str = unary_expression.to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "~2"));
}

TEST_CASE("Columns can be used with the prefix + operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression = +age_column;
    constexpr auto expression_str = unary_expression.to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "+age"));
}

TEST_CASE("Literal expressions can be used with the prefix + operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression = +I(2);
    constexpr auto expression_str = unary_expression.to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "+2"));
}

TEST_CASE("Columns can be used with the prefix - operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression = -age_column;
    constexpr auto expression_str = unary_expression.to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "-age"));
}

TEST_CASE("Literal expressions can be used with the prefix - operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression = -I(2);
    constexpr auto expression_str = unary_expression.to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "-2"));
}

TEST_CASE("Columns can be used with the IS operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = IS(name_column, age_column);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name IS age"));
}

TEST_CASE("Literal expressions can be used with the IS operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = IS(I(2), F(3.14));
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2 IS 3.14"));
}

TEST_CASE("Columns can be used with the IS NOT operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = IS_NOT(name_column, age_column);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name IS NOT age"));
}

TEST_CASE("Literal expressions can be used with the IS NOT operator.", "[test-sql-expressions]") {
    constexpr auto compound_expression = IS_NOT(I(2), F(3.14));
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2 IS NOT 3.14"));
}

TEST_CASE("Columns can be used with the LIKE method.", "[test-sql-expressions]") {
    constexpr auto compound_expression = LIKE(name_column, age_column);
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name LIKE age"));
}

TEST_CASE("Literal expressions can be used with the LIKE method.", "[test-sql-expressions]") {
    constexpr auto compound_expression = LIKE(age_column, S("s%"));
    constexpr auto compound_str = compound_expression.to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "age LIKE 's%'"));
}
