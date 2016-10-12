#pragma once

#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/expression_type.hxx"
#include "sqlite3pp/sql/expressions.hxx"


namespace sqlite3pp {
    namespace sql {

        // Date time literal expressions.
        struct current_time_expression : public expression<current_time_expression> {
            constexpr auto to_str() const { return sql_strings::CURRENT_TIME; }
            constexpr expression_type get_type() const { return expression_type::ANY; }
        };

        static constexpr current_time_expression CURRENT_TIME{};

        struct current_date_expression : public expression<current_date_expression> {
            constexpr auto to_str() const { return sql_strings::CURRENT_DATE; }
            constexpr expression_type get_type() const { return expression_type::ANY; }
        };

        static constexpr current_date_expression CURRENT_DATE{};

        struct current_timestamp_expression : public expression<current_timestamp_expression> {
            constexpr auto to_str() const { return sql_strings::CURRENT_TIMESTAMP; }
            constexpr expression_type get_type() const { return expression_type::ANY; }
        };

        static constexpr current_timestamp_expression CURRENT_TIMESTAMP{};

        // Null literal expression.
        struct null_expression : public expression<null_expression> {
            constexpr auto to_str() const { return sql_strings::NULL_STR; }
            constexpr expression_type get_type() const { return expression_type::NULL_T; }
        };

        static constexpr null_expression NIL{};

        // Integer literal expression.
        template <std::size_t IntegerStrLength>
        class integer_expression : public expression<integer_expression<IntegerStrLength>> {
        public:
            constexpr integer_expression(const char(&integer_str)[IntegerStrLength + 1u], std::int64_t integer)
                    : integer_str{integer_str}, integer{integer} {}

            constexpr auto to_str() const { return integer_str; }
            constexpr expression_type get_type() const { return expression_type::INT; }

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
            constexpr expression_type get_type() const { return expression_type::INT; }

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
            constexpr expression_type get_type() const { return expression_type::REAL; }

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
            constexpr expression_type get_type() const { return expression_type::REAL; }

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
            constexpr expression_type get_type() const { return expression_type::TEXT; }

        private:
            constexpr_string<StrLength> str;
        };

    }
}

// Helper macros for expressions.
#define I(i) (::sqlite3pp::sql::integer_expression<sizeof(#i) - 1u>(#i, i))
#define U(u) (::sqlite3pp::sql::unsigned_integer_expression<sizeof(#u) - 1u>(#u, u))
#define F(f) (::sqlite3pp::sql::float_expression<sizeof(#f) - 1u>(#f, f))
#define D(d) (::sqlite3pp::sql::double_expression<sizeof(#d) - 1u>(#d, d))
#define S(s) (::sqlite3pp::sql::string_expression<sizeof(s) - 1u>(s))
