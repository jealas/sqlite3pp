#include <iostream>

#include "sqlitepp/detail/constexpr_string.hxx"
#include "sqlitepp/sql/column.hxx"
#include "sqlitepp/sql/table.hxx"
#include "sqlitepp/sql/select.hxx"


int main() {
    namespace sql = sqlitepp::sql;

    static constexpr auto name_column = sql::column("name", sqlitepp::sql::column_type::TEXT);
    static constexpr auto age_column = sql::column("age", sqlitepp::sql::column_type::INTEGER);

    static constexpr auto other_column = sql::column("other", sqlitepp::sql::column_type::INTEGER);

    static constexpr auto person = sql::table("VonniesButt", name_column, age_column);

    static constexpr auto schema_person = sql::table("Schema", "Person", sql::column("name", sqlitepp::sql::column_type::INTEGER));

    using sql::from;
    using sql::select;

    static constexpr auto q = select(from[person], name_column, age_column);
}