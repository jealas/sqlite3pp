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

    static constexpr auto name_column = column<name_column_member, column_type::TEXT>("name");

    template <class T>
    struct age_column_member {
        T age;
    };

    static constexpr auto age_column = column<age_column_member, column_type::INTEGER>("age");
}


TEST_CASE("Columns can be used with the parenthesis function.", "[test-sql-expressions]") {
    constexpr auto parenthesis_column_str = P(age_column).to_str();

    REQUIRE(std::equal(parenthesis_column_str.begin(), parenthesis_column_str.end(), "(age)"));
}

TEST_CASE("Literal expressions can be used with the parenthesis function.") {
    constexpr auto parenthesis_literal_str = P(S("hello")).to_str();

    REQUIRE(std::equal(parenthesis_literal_str.begin(), parenthesis_literal_str.end(), "('hello')"));
}

TEST_CASE("Columns can be used with the || operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (age_column || name_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "age||name"));
}

TEST_CASE("Literal expressions can be used with the || operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(123) || F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "123||3.14"));
}

TEST_CASE("Columns can be used with the / operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column / age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name/age"));
}

TEST_CASE("Literal expressions can be used with the / operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (F(2.718) / F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718/3.14"));
}

TEST_CASE("Columns can be used with the % operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column % age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name%age"));
}

TEST_CASE("Literal expressions can be used with the % operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (F(2.718) % F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718%3.14"));
}

TEST_CASE("Columns can be used with the + operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column + age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name+age"));
}

TEST_CASE("Literal expressions can be used with the + operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (F(2.718) + F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718+3.14"));
}

TEST_CASE("Columns can be used with the - operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column - age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name-age"));
}

TEST_CASE("Literal expressions can be used with the - operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (F(2.718) - F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718-3.14"));
}

TEST_CASE("Columns can be used with the << operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column << age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name<<age"));
}

TEST_CASE("Literal expressions can be used with the << operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (F(2.718) << F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718<<3.14"));
}

TEST_CASE("Columns can be used with the >> operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column >> age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name>>age"));
}

TEST_CASE("Literal expressions can be used with the >> operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (F(2.718) >> F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2.718>>3.14"));
}

TEST_CASE("Columns can be used with the & operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column & age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name&age"));
}

TEST_CASE("Literal expressions can be used with the & operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) & I(3)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2&3"));
}

TEST_CASE("Columns can be used with the | operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column | age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name|age"));
}

TEST_CASE("Literal expressions can be used with the | operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) | I(3)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2|3"));
}

TEST_CASE("Columns can be used with the < operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column < age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name<age"));
}

TEST_CASE("Literal expressions can be used with the < operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) < F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2<3.14"));
}

TEST_CASE("Columns can be used with the > operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column > age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name>age"));
}

TEST_CASE("Literal expressions can be used with the > operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) > F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2>3.14"));
}

TEST_CASE("Columns can be used with the <= operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column <= age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name<=age"));
}

TEST_CASE("Literal expressions can be used with the <= operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) <= F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2<=3.14"));
}

TEST_CASE("Columns can be used with the >= operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column >= age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name>=age"));
}

TEST_CASE("Literal expressions can be used with the >= operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) >= F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2>=3.14"));
}

TEST_CASE("Columns can be used with the == operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column == age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name==age"));
}

TEST_CASE("Literal expressions can be used with the == operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) == F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2==3.14"));
}

TEST_CASE("Columns can be used with the != operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (name_column != age_column).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "name!=age"));
}

TEST_CASE("Literal expressions can be used with the != operator.", "[test-sql-expressions]") {
    constexpr auto compound_str = (I(2) != F(3.14)).to_str();

    REQUIRE(std::equal(compound_str.begin(), compound_str.end(), "2!=3.14"));
}

TEST_CASE("Columns can be used with the ~ operator.", "[test-sql-expressions]") {
    constexpr auto expression_str = (~age_column).to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "~age"));
}

TEST_CASE("Literal expressions can be used with the ~ operator.", "[test-sql-expressions]") {
    constexpr auto expression_str = (~I(2)).to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "~2"));
}

TEST_CASE("Columns can be used with the prefix + operator.", "[test-sql-expressions]") {
    constexpr auto expression_str = (+age_column).to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "+age"));
}

TEST_CASE("Literal expressions can be used with the prefix + operator.", "[test-sql-expressions]") {
    constexpr auto expression_str = (+I(2)).to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "+2"));
}

TEST_CASE("Columns can be used with the prefix - operator.", "[test-sql-expressions]") {
    constexpr auto expression_str = (-age_column).to_str();

    REQUIRE(std::equal(expression_str.begin(), expression_str.end(), "-age"));
}

TEST_CASE("Literal expressions can be used with the prefix - operator.", "[test-sql-expressions]") {
    constexpr auto unary_expression_str = (-I(2)).to_str();

    REQUIRE(std::equal(unary_expression_str.begin(), unary_expression_str.end(), "-2"));
}

TEST_CASE("IS.NOT construct can be used with NIL.", "[test-sql-expressions]") {
    constexpr auto is_not_null_expression_str = NIL.IS.NOT(NIL).to_str();

    REQUIRE(std::equal(is_not_null_expression_str.begin(), is_not_null_expression_str.end(), "NULL IS NOT NULL"));
}

TEST_CASE("IS.NOT construct can be used with integer literal constants.", "[test-sql-expressions]") {
    constexpr auto is_not_int_expression_str = I(10).IS.NOT(I(20)).to_str();

    REQUIRE(std::equal(is_not_int_expression_str.begin(), is_not_int_expression_str.end(), "10 IS NOT 20"));
}

TEST_CASE("IS.NOT construct can be used with columns.", "[test-sql-expressions]") {
    constexpr auto column_is_not_null_str = age_column.IS.NOT(NIL).to_str();

    REQUIRE(std::equal(column_is_not_null_str.begin(), column_is_not_null_str.end(), "age IS NOT NULL"));
}

TEST_CASE("NOTNULL construct can be used with literal constants.", "[test-sql-expressions]") {
    constexpr auto literal_notnull_str = F(4.5).NOTNULL().to_str();

    REQUIRE(std::equal(literal_notnull_str.begin(), literal_notnull_str.end(), "4.5 NOTNULL"));
}

TEST_CASE("NOTNULL construct can be used with columns.", "[test-sql-expressions]") {
    constexpr auto column_notnull_str = age_column.NOTNULL().to_str();

    REQUIRE(std::equal(column_notnull_str.begin(), column_notnull_str.end(), "age NOTNULL"));
}

TEST_CASE("Bind parameters can be used with IS.NOT expressions.", "[test-sql-expressions]") {
    constexpr auto is_not_bind_str = name_column.IS.NOT(_).to_str();

    REQUIRE(std::equal(is_not_bind_str.begin(), is_not_bind_str.end(), "name IS NOT ?"));
}

TEST_CASE("Bind parameters can be used as expressions with the IS.NOT construct.", "[test-sql-expressions]") {
    constexpr auto bind_parameter_is_not_str = _.IS.NOT(NIL).to_str();

    REQUIRE(std::equal(bind_parameter_is_not_str.begin(), bind_parameter_is_not_str.end(), "? IS NOT NULL"));
}
