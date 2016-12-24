#pragma once

#include <sqlite3pp/query.hxx>
#include "sqlite3pp/sql/create_table_statement.hxx"


namespace sqlite3pp {
    namespace sql {

        class create_statement : public create_table_syntax_base<create_statement> {
        public:
            constexpr create_statement()
                    : TEMPORARY{*this},
                      TEMP{*this} {}

            constexpr auto to_str() const { return sql_strings::CREATE; }

            create_temporary_table_syntax<create_statement> TEMPORARY;
            create_temp_table_syntax<create_statement> TEMP;
        };


        class create_syntax: public create_table_syntax_base<create_syntax> {
        public:
            constexpr create_syntax()
                : TEMP{*this},
                  TEMPORARY{*this},
                  TABLE{*this} {}

            create_temp_table_syntax<create_syntax> TEMP;
            create_temporary_table_syntax<create_syntax> TEMPORARY;
            create_table_table_syntax<create_syntax> TABLE;

            constexpr auto to_str() const { return sql_strings::CREATE; }
        };

    }
}
