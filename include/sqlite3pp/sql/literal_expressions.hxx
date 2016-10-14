#pragma once

#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/expressions.hxx"


namespace sqlite3pp {
    namespace sql {

        // Bind parameter expression.
        struct bind_parameter : public expression<bind_parameter> {
            constexpr auto to_str() const { return sql_strings::QUESTION_MARK; }
        };

        // Date time literal expressions.
        struct current_time_expression : public expression<current_time_expression> {
            constexpr auto to_str() const { return sql_strings::CURRENT_TIME; }
        };

        struct current_date_expression : public expression<current_date_expression> {
            constexpr auto to_str() const { return sql_strings::CURRENT_DATE; }
        };

        struct current_timestamp_expression : public expression<current_timestamp_expression> {
            constexpr auto to_str() const { return sql_strings::CURRENT_TIMESTAMP; }
        };

        // Null literal expression.
        struct null_expression : public expression<null_expression> {
            constexpr auto to_str() const { return sql_strings::NULL_STR; }
        };

        // Integer literal expression.
        template <std::size_t IntegerStrLength>
        class integer_expression : public expression<integer_expression<IntegerStrLength>> {
        public:
            constexpr integer_expression(const char(&integer_str)[IntegerStrLength + 1u], std::int64_t integer)
                    : integer_str{integer_str}, integer{integer} {}

            constexpr auto to_str() const { return integer_str; }

        private:
            constexpr_string<IntegerStrLength> integer_str;
            std::int64_t integer;
        };

        // Unsigned literal expression.
        template <std::size_t UnsignedStrLength>
        class unsigned_integer_expression : public expression<unsigned_integer_expression<UnsignedStrLength>> {
        public:
            constexpr unsigned_integer_expression(const char(&unsigned_str)[UnsignedStrLength + 1u], std::uint64_t unsigned_integer)
                    : unsigned_integer_str{unsigned_str}, unsigned_integer{unsigned_integer} {}

            constexpr auto to_str() const { return unsigned_integer_str; }

        private:
            constexpr_string<UnsignedStrLength> unsigned_integer_str;
            std::uint64_t unsigned_integer;
        };

        // Float literal expressions.
        template <std::size_t FloatStrLength>
        class float_expression : public expression<float_expression<FloatStrLength>> {
        public:
            constexpr float_expression(const char(&float_str)[FloatStrLength + 1u], float float_value)
                : float_str{float_str}, float_value{float_value} {}

            constexpr auto to_str() const { return float_str; }

        private:
            constexpr_string<FloatStrLength> float_str;
            float float_value;
        };

        template <std::size_t DoubleStrLength>
        class double_expression : public expression<double_expression<DoubleStrLength>> {
        public:
            constexpr double_expression(const char(&double_str)[DoubleStrLength + 1u], double double_value)
                : double_str{double_str}, double_value{double_value} {}

            constexpr auto to_str() const { return double_str; }

        private:
            constexpr_string<DoubleStrLength> double_str;
            double double_value;
        };

        // String literal expression.
        template <std::size_t StrLength>
        class string_expression : public expression<string_expression<StrLength>> {
        public:
            constexpr string_expression(const char(&str)[StrLength + 1u]) : str{str} {}

            constexpr auto to_str() const { return str.join(sql_strings::SINGLE_QUOTE, sql_strings::SINGLE_QUOTE); }

        private:
            constexpr_string<StrLength> str;
        };

    }
}
