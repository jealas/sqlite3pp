#pragma once

#include "sqlite3pp/sql/serializable.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"


namespace sqlite3pp {
    namespace sql {

        template <class T>
        class data_type : public serializable<T> {};

        struct integer_type : public data_type<integer_type> {
            constexpr auto to_str() const { return sql_strings::INTEGER; }
        };

        struct int_type : public data_type<int_type> {
            constexpr auto to_str() const { return sql_strings::INT; }
        };

        struct tinyint_type : public data_type<tinyint_type> {
            constexpr auto to_str() const { return sql_strings::TINYINT; }
        };

        struct smallint_type : public data_type<smallint_type> {
            constexpr auto to_str() const { return sql_strings::SMALLINT; }
        };

        struct mediumint_type : public data_type<mediumint_type> {
            constexpr auto to_str() const { return sql_strings::MEDIUMINT; }
        };

        struct bigint_type : public data_type<bigint_type> {
            constexpr auto to_str() const { return sql_strings::BIGINT; }
        };

        struct real_type : public data_type<real_type> {
            constexpr auto to_str() const { return sql_strings::REAL; }
        };

        struct double_type : public data_type<double_type> {
            constexpr auto to_str() const { return sql_strings::DOUBLE; }
        };

        struct float_type : public data_type<float_type> {
            constexpr auto to_str() const { return sql_strings::FLOAT; }
        };

        struct text_type : public data_type<text_type> {
            constexpr auto to_str() const { return sql_strings::TEXT; }
        };

        struct char_type : public data_type<char_type> {
            constexpr auto to_str() const { return sql_strings::CHAR; }
        };

        struct clob_type : public data_type<clob_type> {
            constexpr auto to_str() const { return sql_strings::CLOB; }
        };

        struct varchar_type : public data_type<varchar_type> {
            constexpr auto to_str() const { return sql_strings::VARCHAR; }
        };

        struct blob_type : public data_type<blob_type> {
            constexpr auto to_str() const { return sql_strings::BLOB; }
        };

        struct numeric_type : public data_type<numeric_type> {
            constexpr auto to_str() const { return sql_strings::NUMERIC; }
        };

        struct decimal_type : public data_type<decimal_type> {
            constexpr auto to_str() const { return sql_strings::DECIMAL; }
        };

        struct boolean_type : public data_type<boolean_type> {
            constexpr auto to_str() const { return sql_strings::BOOLEAN; }
        };

        struct date_type : public data_type<date_type> {
            constexpr auto to_str() const { return sql_strings::DATE; }
        };

        struct datetime_type : public data_type<datetime_type> {
            constexpr auto to_str() const { return sql_strings::DATETIME; }
        };

    }
}
