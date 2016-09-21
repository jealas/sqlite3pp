#pragma once

#include <cstdint>

#include "sql_strings.hxx"


namespace sqlite3pp {
    namespace sql {

        enum class column_type : std::uint8_t {
            INTEGER,
            BLOB,
            REAL,
            TEXT,
        };

        template <column_type ColumnType>
        constexpr auto get_column_type_str();

        template <>
        constexpr auto get_column_type_str<column_type::INTEGER>() { return sql_strings::INTEGER; };

        template <>
        constexpr auto get_column_type_str<column_type::BLOB>() { return sql_strings::BLOB; }

        template <>
        constexpr auto get_column_type_str<column_type::REAL>() { return sql_strings::REAL; }

        template <>
        constexpr auto get_column_type_str<column_type::TEXT>() { return sql_strings::TEXT; }

    }
}