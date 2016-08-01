#pragma once

#include "sqlitepp/detail/constexpr_string.hxx"

namespace sqlitepp {
    namespace sql {

        template <class CharT>
        struct sql_strings;

        template <>
        struct sql_strings<char> {
            static constexpr auto COMMA = sqlitepp::detail::make_constexpr_string(",");
            static constexpr auto EMPTY = sqlitepp::detail::make_constexpr_string("");
            static constexpr auto SPACE = sqlitepp::detail::make_constexpr_string(" ");
            static constexpr auto QUESTION_MARK = sqlitepp::detail::make_constexpr_string("?");
            static constexpr auto ASTERISK = sqlitepp::detail::make_constexpr_string("*");
            static constexpr auto DOT = sqlitepp::detail::make_constexpr_string(".");

            static constexpr auto SELECT = sqlitepp::detail::make_constexpr_string("SELECT");
            static constexpr auto FROM = sqlitepp::detail::make_constexpr_string("FROM");

            static constexpr auto NULL_STR = sqlitepp::detail::make_constexpr_string("NULL");
            static constexpr auto INTEGER = sqlitepp::detail::make_constexpr_string("INTEGER");
            static constexpr auto DOUBLE = sqlitepp::detail::make_constexpr_string("DOUBLE");
            static constexpr auto TEXT = sqlitepp::detail::make_constexpr_string("TEXT");
            static constexpr auto BLOB = sqlitepp::detail::make_constexpr_string("BLOB");
        };

        template <>
        struct sql_strings<char16_t> {
        };

        constexpr const decltype(sql_strings<char>::COMMA) sql_strings<char>::COMMA;
        constexpr const decltype(sql_strings<char>::EMPTY) sql_strings<char>::EMPTY;
        constexpr const decltype(sql_strings<char>::SPACE) sql_strings<char>::SPACE;
        constexpr const decltype(sql_strings<char>::QUESTION_MARK) sql_strings<char>::QUESTION_MARK;
        constexpr const decltype(sql_strings<char>::ASTERISK) sql_strings<char>::ASTERISK;
        constexpr const decltype(sql_strings<char>::DOT) sql_strings<char>::DOT;

        constexpr const decltype(sql_strings<char>::SELECT) sql_strings<char>::SELECT;
        constexpr const decltype(sql_strings<char>::FROM) sql_strings<char>::FROM;

        constexpr const decltype(sql_strings<char>::NULL_STR) sql_strings<char>::NULL_STR;
        constexpr const decltype(sql_strings<char>::INTEGER) sql_strings<char>::INTEGER;
        constexpr const decltype(sql_strings<char>::DOUBLE) sql_strings<char>::DOUBLE;
        constexpr const decltype(sql_strings<char>::TEXT) sql_strings<char>::TEXT;
        constexpr const decltype(sql_strings<char>::BLOB) sql_strings<char>::BLOB;

    }
}