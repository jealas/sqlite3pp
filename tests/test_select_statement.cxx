#include <catch.hpp>
#include <algorithm>

#include "sqlite3pp/query.hxx"

namespace {

    using namespace sqlite3pp;

    template <class T>
    struct name_column_member {
        T name;
    };

    static constexpr auto name = column<name_column_member>("name", TEXT);

    template <class T>
    struct age_column_member {
        T age;
    };

    static constexpr auto age = column<age_column_member>("age", INTEGER);

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
    constexpr auto select_str = SELECT(age, name).FROM(person)
                                .WHERE(age == I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age==10"));
}

TEST_CASE("Can use SELECT ALL FROM WHERE statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.ALL(age, name).FROM(person)
                                .WHERE(name != S("joe")).to_str();


    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT ALL age,name FROM person WHERE name!='joe'"));
}

TEST_CASE("Can use SELECT DISTINCT FROM WHERE statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT.DISTINCT(age, name)
                                .FROM(person)
                                .WHERE((age < I(20)).AND(name != S("tom"))).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT DISTINCT age,name FROM person WHERE age<20 AND name!='tom'"));
}

TEST_CASE("Can use SELECT FROM GROUP BY statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .GROUP.BY(age).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person GROUP BY age"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2"));
}

TEST_CASE("Can use SELECT FROM ORDER BY statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age"));
}

TEST_CASE("Can use SELECT FROM LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .LIMIT(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person LIMIT 100"));
}

TEST_CASE("Can use SELECT FROM WHERE LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .LIMIT(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 LIMIT 100"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .LIMIT(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name LIMIT 100"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .LIMIT(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 LIMIT 100"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age)
                                .LIMIT(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age LIMIT 100"));
}

TEST_CASE("Can use SELECT FROM LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age)
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM WHERE LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY LIMIT OFFSET range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age)
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY ASC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.ASC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age ASC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY ASC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.ASC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age ASC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY ASC LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.ASC())
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age ASC LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY DESC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.DESC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age DESC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY DESC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.DESC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age DESC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY DESC LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.DESC())
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age DESC LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE BYTE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.COLLATE(BYTE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE BYTE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE BYTE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.COLLATE(BYTE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE BYTE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE BYTE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.COLLATE(BYTE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE BYTE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE ASC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).ASC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE ASC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE ASC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).ASC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE ASC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE ASC LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).ASC())
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE ASC LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE BYTE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.COLLATE(BYTE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE BYTE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE BYTE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.COLLATE(BYTE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE BYTE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE BYTE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .ORDER.BY(age.COLLATE(BYTE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE BYTE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE DESC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).DESC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE DESC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE BYTE DESC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(BYTE).DESC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE BYTE DESC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE NOCASE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.COLLATE(NOCASE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE NOCASE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE NOCASE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.COLLATE(NOCASE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE NOCASE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE NOCASE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.COLLATE(NOCASE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE NOCASE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE ASC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).ASC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE ASC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE ASC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).ASC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE ASC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE ASC LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).ASC())
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE ASC LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE NOCASE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.COLLATE(NOCASE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE NOCASE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE NOCASE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.COLLATE(NOCASE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE NOCASE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE NOCASE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.COLLATE(NOCASE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE NOCASE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE DESC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).DESC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE DESC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE NOCASE DESC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(NOCASE).DESC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE NOCASE DESC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE RTRIM ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.COLLATE(RTRIM).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE RTRIM ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE RTRIM ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.COLLATE(RTRIM).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE RTRIM ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE RTRIM ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.COLLATE(RTRIM).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE RTRIM ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM ASC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).ASC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM ASC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM ASC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).ASC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM ASC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM ASC LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).ASC())
                                .LIMIT(I(10))
                                .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM ASC LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE RTRIM DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .ORDER.BY(age.COLLATE(RTRIM).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE RTRIM DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE RTRIM DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .ORDER.BY(age.COLLATE(RTRIM).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE RTRIM DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE RTRIM DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .ORDER.BY(age.COLLATE(RTRIM).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE RTRIM DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM DESC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).DESC())
                                .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM DESC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE RTRIM DESC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
                                .FROM(person)
                                .WHERE(age > I(50))
                                .GROUP.BY(name)
                                .HAVING(COUNT(age) > I(2))
                                .ORDER.BY(age.COLLATE(RTRIM).DESC())
                                .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE RTRIM DESC LIMIT 100,10"));
}

namespace { constexpr auto MYCOLLATION = make_custom_collation("MYCOLLATION"); }

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE MYCOLLATION ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE MYCOLLATION ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE MYCOLLATION ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE MYCOLLATION ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE MYCOLLATION ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE MYCOLLATION ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION ASC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION ASC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION ASC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC())
            .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION ASC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION ASC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC())
            .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION ASC LIMIT 100,10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION ASC LIMIT OFFSET statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).ASC())
            .LIMIT(I(10))
            .OFFSET(I(100)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION ASC LIMIT 10 OFFSET 100"));
}

TEST_CASE("Can use SELECT FROM ORDER BY COLLATE MYCOLLATION DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .ORDER.BY(age.COLLATE(MYCOLLATION).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person ORDER BY age COLLATE MYCOLLATION DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE ORDER BY COLLATE MYCOLLATION DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .ORDER.BY(age.COLLATE(MYCOLLATION).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 ORDER BY age COLLATE MYCOLLATION DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY ORDER BY COLLATE MYCOLLATION DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .ORDER.BY(age.COLLATE(MYCOLLATION).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name ORDER BY age COLLATE MYCOLLATION DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION DESC statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).DESC()).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION DESC"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION DESC LIMIT statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).DESC())
            .LIMIT(I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION DESC LIMIT 10"));
}

TEST_CASE("Can use SELECT FROM WHERE GROUP BY HAVING ORDER BY COLLATE MYCOLLATION DESC LIMIT range statement with columns.", "[test-select-statement]") {
    constexpr auto select_str = SELECT(age, name)
            .FROM(person)
            .WHERE(age > I(50))
            .GROUP.BY(name)
            .HAVING(COUNT(age) > I(2))
            .ORDER.BY(age.COLLATE(MYCOLLATION).DESC())
            .LIMIT(I(100), I(10)).to_str();

    REQUIRE(std::equal(select_str.begin(), select_str.end(), "SELECT age,name FROM person WHERE age>50 GROUP BY name HAVING COUNT(age)>2 ORDER BY age COLLATE MYCOLLATION DESC LIMIT 100,10"));
}
