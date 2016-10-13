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

TEST_CASE("IS NOT can be used with NIL.", "[test-sql-expressions]") {
    constexpr auto is_not_null_expression_str = NIL.IS.NOT(NIL).to_str();

    REQUIRE(std::equal(is_not_null_expression_str.begin(), is_not_null_expression_str.end(), "NULL IS NOT NULL"));
}

TEST_CASE("IS NOT can be used with integer literal constants.", "[test-sql-expressions]") {
    constexpr auto is_not_int_expression_str = I(10).IS.NOT(I(20)).to_str();

    REQUIRE(std::equal(is_not_int_expression_str.begin(), is_not_int_expression_str.end(), "10 IS NOT 20"));
}

TEST_CASE("IS NOT can be used with columns.", "[test-sql-expressions]") {
    constexpr auto column_is_not_null_str = age_column.IS.NOT(NIL).to_str();

    REQUIRE(std::equal(column_is_not_null_str.begin(), column_is_not_null_str.end(), "age IS NOT NULL"));
}

TEST_CASE("Bind parameters can be used with IS NOT expressions.", "[test-sql-expressions]") {
    constexpr auto is_not_bind_str = name_column.IS.NOT(_).to_str();

    REQUIRE(std::equal(is_not_bind_str.begin(), is_not_bind_str.end(), "name IS NOT ?"));
}

TEST_CASE("Bind parameters can be used as expressions with the IS NOT expression.", "[test-sql-expressions]") {
    constexpr auto bind_parameter_is_not_str = _.IS.NOT(NIL).to_str();

    REQUIRE(std::equal(bind_parameter_is_not_str.begin(), bind_parameter_is_not_str.end(), "? IS NOT NULL"));
}

TEST_CASE("IS construct can be used with NIL.", "[test-sql-expressions]") {
    constexpr auto is_null_expression_str = NIL.IS(NIL).to_str();

    REQUIRE(std::equal(is_null_expression_str.begin(), is_null_expression_str.end(), "NULL IS NULL"));
}

TEST_CASE("IS construct can be used with integer literal constants.", "[test-sql-expressions]") {
    constexpr auto is_int_expression_str = I(10).IS(I(20)).to_str();

    REQUIRE(std::equal(is_int_expression_str.begin(), is_int_expression_str.end(), "10 IS 20"));
}

TEST_CASE("IS construct can be used with columns.", "[test-sql-expressions]") {
    constexpr auto column_is_null_str = age_column.IS(NIL).to_str();

    REQUIRE(std::equal(column_is_null_str.begin(), column_is_null_str.end(), "age IS NULL"));
}

TEST_CASE("Literals can be used with AND expression.", "[test-sql-expression]") {
    constexpr auto and_expression_str = I(1).AND(I(0)).to_str();

    REQUIRE(std::equal(and_expression_str.begin(), and_expression_str.end(), "1 AND 0"));
}

TEST_CASE("Columns can be used with AND expression.", "[test-sql-expression]") {
    constexpr auto and_expression_str = age_column.AND(name_column).to_str();

    REQUIRE(std::equal(and_expression_str.begin(), and_expression_str.end(), "age AND name"));
}

TEST_CASE("Literals can be used with OR expression.", "[test-sql-expression]") {
    constexpr auto or_expression_str = I(1).OR(I(0)).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "1 OR 0"));
}

TEST_CASE("Columns can be used with OR expression.", "[test-sql-expression]") {
    constexpr auto or_expression_str = age_column.OR(name_column).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "age OR name"));
}

TEST_CASE("NOT function can be used with columns.", "[test-sql-expression]") {
    constexpr auto not_expression_str = NOT(age_column.OR(name_column)).to_str();

    REQUIRE(std::equal(not_expression_str.begin(), not_expression_str.end(), "NOT(age OR name)"));
}

TEST_CASE("NOT function can be used with arbitrary expressions.", "[test-sql-expression]") {
    constexpr auto not_expression_str = NOT(I(2) * F(10.1)).to_str();

    REQUIRE(std::equal(not_expression_str.begin(), not_expression_str.end(), "NOT(2*10.1)"));
}

TEST_CASE("LIKE expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.LIKE(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age LIKE name"));
}

TEST_CASE("LIKE expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").LIKE(S("n%")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' LIKE 'n%'"));
}

TEST_CASE("GLOB expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.GLOB(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age GLOB name"));
}

TEST_CASE("GLOB expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").GLOB(S("n*")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' GLOB 'n*'"));
}

TEST_CASE("REGEXP expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.REGEXP(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age REGEXP name"));
}

TEST_CASE("REGEXP expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").REGEXP(S("[a-zA-Z]")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' REGEXP '[a-zA-Z]'"));
}

TEST_CASE("MATCH expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.MATCH(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age MATCH name"));
}

TEST_CASE("MATCH expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").MATCH(S("name")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' MATCH 'name'"));
}

TEST_CASE("NOT LIKE expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.NOT.LIKE(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age NOT LIKE name"));
}

TEST_CASE("NOT LIKE expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").NOT.LIKE(S("n%")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' NOT LIKE 'n%'"));
}

TEST_CASE("NOT GLOB expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.NOT.GLOB(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age NOT GLOB name"));
}

TEST_CASE("NOT GLOB expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").NOT.GLOB(S("n*")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' NOT GLOB 'n*'"));
}

TEST_CASE("NOT REGEXP expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.NOT.REGEXP(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age NOT REGEXP name"));
}

TEST_CASE("NOT REGEXP expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").NOT.REGEXP(S("[a-zA-Z]")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' NOT REGEXP '[a-zA-Z]'"));
}

TEST_CASE("NOT MATCH expression can be used with columns.", "[test-sql-expression]") {
    constexpr auto like_expression_str = age_column.NOT.MATCH(name_column).to_str();

    REQUIRE(std::equal(like_expression_str.begin(), like_expression_str.end(), "age NOT MATCH name"));
}

TEST_CASE("NOT MATCH expression can be used with literals.", "[test-sql-expression]") {
    constexpr auto or_expression_str = S("name").NOT.MATCH(S("name")).to_str();

    REQUIRE(std::equal(or_expression_str.begin(), or_expression_str.end(), "'name' NOT MATCH 'name'"));
}

TEST_CASE("BETWEEN can be used with literal expressions.", "[test-sql-expression]") {
    constexpr auto between_expression_str = I(1).BETWEEN(I(0), I(2)).to_str();

    REQUIRE(std::equal(between_expression_str.begin(), between_expression_str.end(), "1 BETWEEN 0 AND 2"));
}

TEST_CASE("BETWEEN can be used with columns.", "[test-sql-expression]") {
    constexpr auto between_expression_str = age_column.BETWEEN(I(18), I(21)).to_str();

    REQUIRE(std::equal(between_expression_str.begin(), between_expression_str.end(), "age BETWEEN 18 AND 21"));
}

TEST_CASE("NOT BETWEEN can be used with literal expressions.", "[test-sql-expression]") {
    constexpr auto not_between_expression_str = I(1).NOT.BETWEEN(I(0), I(2)).to_str();

    REQUIRE(std::equal(not_between_expression_str.begin(), not_between_expression_str.end(), "1 NOT BETWEEN 0 AND 2"));
}

TEST_CASE("NOT BETWEEN can be used with columns.", "[test-sql-expression]") {
    constexpr auto not_between_expression_str = age_column.NOT.BETWEEN(I(18), I(21)).to_str();

    REQUIRE(std::equal(not_between_expression_str.begin(), not_between_expression_str.end(), "age NOT BETWEEN 18 AND 21"));
}
