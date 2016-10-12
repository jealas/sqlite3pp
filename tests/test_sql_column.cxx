#include <catch.hpp>
#include <algorithm>

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/column_type.hxx"


namespace {

    using namespace sqlite3pp::sql;

    template <class T>
    struct name_column_member {
        T name;
    };

    static constexpr auto name_column = column<name_column_member, column_type::TEXT>("name");
}


TEST_CASE("columns are serializable.", "test-sql-column") {
    constexpr auto name_str = name_column.to_str();

    REQUIRE(std::equal(name_str.begin(), name_str.end(), "name"));
}
