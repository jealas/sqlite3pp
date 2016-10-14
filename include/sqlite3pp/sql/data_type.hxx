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

        static constexpr integer_type INTEGER{};
        static constexpr int_type INT{};

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

    }
}
