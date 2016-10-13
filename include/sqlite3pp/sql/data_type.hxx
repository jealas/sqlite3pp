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

        struct real_type : public data_type<real_type> {
            constexpr auto to_str() const { return sql_strings::REAL; }
        };

        struct text_type : public data_type<text_type> {
            constexpr auto to_str() const { return sql_strings::TEXT; }
        };

        struct blob_type : public data_type<blob_type> {
            constexpr auto to_str() const { return sql_strings::BLOB; }
        };

        static constexpr integer_type INTEGER{};
        static constexpr real_type REAL{};
        static constexpr text_type TEXT{};
        static constexpr blob_type BLOB{};

    }
}
