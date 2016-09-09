#pragma once

#include "sqlitepp/detail/constexpr_string.hxx"


namespace {
    using namespace sqlitepp::detail;
}

namespace sqlitepp {
    namespace sql {

        struct sql_strings {
            static constexpr auto COMMA = make_constexpr_string(",");
            static constexpr auto SPACE = make_constexpr_string(" ");
            static constexpr auto QUESTION_MARK = make_constexpr_string("?");
            static constexpr auto ASTERISK = make_constexpr_string("*");
            static constexpr auto DOT = make_constexpr_string(".");
            static constexpr auto SINGLE_QUOTE = make_constexpr_string("'");
            static constexpr auto DOUBLE_QUOTE = make_constexpr_string("\"");

            static constexpr auto SELECT = make_constexpr_string("SELECT");
            static constexpr auto FROM = make_constexpr_string("FROM");

            static constexpr auto NULL_STR = make_constexpr_string("NULL");
            static constexpr auto INTEGER = make_constexpr_string("INTEGER");
            static constexpr auto REAL = make_constexpr_string("REAL");
            static constexpr auto TEXT = make_constexpr_string("TEXT");
            static constexpr auto BLOB = make_constexpr_string("BLOB");

            static constexpr auto CURRENT_TIME = make_constexpr_string("CURRENT_TIME");
            static constexpr auto CURRENT_DATE = make_constexpr_string("CURRENT_DATE");
            static constexpr auto CURRENT_TIMESTAMP = make_constexpr_string("CURRENT_TIMESTAMP");
        };

        constexpr decltype(sql_strings::COMMA) sql_strings::COMMA;
        constexpr decltype(sql_strings::SPACE) sql_strings::SPACE;
        constexpr decltype(sql_strings::QUESTION_MARK) sql_strings::QUESTION_MARK;
        constexpr decltype(sql_strings::ASTERISK) sql_strings::ASTERISK;
        constexpr decltype(sql_strings::DOT) sql_strings::DOT;
        constexpr decltype(sql_strings::SINGLE_QUOTE) sql_strings::SINGLE_QUOTE;
        constexpr decltype(sql_strings::DOUBLE_QUOTE) sql_strings::DOUBLE_QUOTE;

        constexpr decltype(sql_strings::SELECT) sql_strings::SELECT;
        constexpr decltype(sql_strings::FROM) sql_strings::FROM;

        constexpr decltype(sql_strings::NULL_STR) sql_strings::NULL_STR;
        constexpr decltype(sql_strings::INTEGER) sql_strings::INTEGER;
        constexpr decltype(sql_strings::REAL) sql_strings::REAL;
        constexpr decltype(sql_strings::TEXT) sql_strings::TEXT;
        constexpr decltype(sql_strings::BLOB) sql_strings::BLOB;

        constexpr decltype(sql_strings::CURRENT_TIME) sql_strings::CURRENT_TIME;
        constexpr decltype(sql_strings::CURRENT_DATE) sql_strings::CURRENT_DATE;
        constexpr decltype(sql_strings::CURRENT_TIMESTAMP) sql_strings::CURRENT_TIMESTAMP;
    }
}