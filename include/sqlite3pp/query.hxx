#pragma once

#include "sqlite3pp/sql/data_type.hxx"
#include "sqlite3pp/sql/literal_expressions.hxx"
#include "sqlite3pp/sql/expression_operators.hxx"
#include "sqlite3pp/sql/all.hxx"
#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/table.hxx"
#include "sqlite3pp/detail/constexpr_string.hxx"
#include "sqlite3pp/sql/select_statement.hxx"
#include "sqlite3pp/sql/insert_statement.hxx"
#include "sqlite3pp/sql/column_operators.hxx"
#include "sqlite3pp/sql/update_statement.hxx"

namespace { using namespace sqlite3pp::sql; }


namespace sqlite3pp {

    // Data types.
    static constexpr integer_type INTEGER{};
    static constexpr int_type INT{};
    static constexpr tinyint_type TINYINT{};
    static constexpr smallint_type SMALLINT{};
    static constexpr mediumint_type MEDIUMINT{};
    static constexpr bigint_type BIGINT{};

    static constexpr real_type REAL{};
    static constexpr double_type DOUBLE{};
    static constexpr float_type FLOAT{};

    static constexpr text_type TEXT{};
    static constexpr char_type CHAR{};
    static constexpr clob_type CLOB{};
    static constexpr varchar_type VARCHAR{};

    static constexpr blob_type BLOB{};

    static constexpr numeric_type NUMERIC{};
    static constexpr decimal_type DECIMAL{};
    static constexpr boolean_type BOOLEAN{};
    static constexpr date_type DATE{};
    static constexpr datetime_type DATETIME{};

    // Literal expressions.
    static constexpr bind_parameter _{};
    static constexpr current_time_expression CURRENT_TIME{};
    static constexpr current_date_expression CURRENT_DATE{};
    static constexpr current_timestamp_expression CURRENT_TIMESTAMP{};

    #ifdef NULL
    #undef NULL
    #endif

    static constexpr null_expression NULL{};

    // Expression operators.
    using namespace sqlite3pp::sql::operators;

    // Table and Column APIs.
    template <std::size_t NameLength>
    constexpr auto column(const char (&name)[NameLength]) {
        auto name_str = detail::make_constexpr_string(name);

        return column_t<decltype(name_str)>{name_str};
    }

    template<template <class ...> class TableT, std::size_t TableNameLength, class ... ColumnT>
    constexpr auto table(const char (&name)[TableNameLength], const column_base<ColumnT> & ... columns) {
        auto name_str = detail::make_constexpr_string(name);

        return table_t<TableT, decltype(name_str), ColumnT...>{name_str, columns...};
    }

    // Query API.
    static constexpr all_t ALL{};

    static constexpr select_member SELECT{};
    static constexpr insert_member INSERT{};
    static constexpr update_member UPDATE{};

    static constexpr collate_byte BYTE{};
    static constexpr collate_nocase NOCASE{};
    static constexpr collate_rtrim RTRIM{};

}

// Helper macros for literal expressions.
#define I(i) (::sqlite3pp::sql::integer_expression<sizeof(#i) - 1u>(#i, i))
#define U(u) (::sqlite3pp::sql::unsigned_integer_expression<sizeof(#u) - 1u>(#u, u))
#define F(f) (::sqlite3pp::sql::float_expression<sizeof(#f) - 1u>(#f, f))
#define D(d) (::sqlite3pp::sql::double_expression<sizeof(#d) - 1u>(#d, d))
#define S(s) (::sqlite3pp::sql::string_expression<sizeof(s) - 1u>(s))

