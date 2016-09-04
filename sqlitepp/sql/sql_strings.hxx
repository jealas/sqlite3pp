#pragma once

#include "sqlitepp/detail/constexpr_string.hxx"


namespace {
    using namespace sqlitepp::detail;
}

namespace sqlitepp {
    namespace sql {

        struct sql_strings {
            static constexpr auto COMMA = make_constexpr_string(",");
            static constexpr auto EMPTY = make_constexpr_string("");
            static constexpr auto SPACE = make_constexpr_string(" ");
            static constexpr auto QUESTION_MARK = make_constexpr_string("?");
            static constexpr auto ASTERISK = make_constexpr_string("*");
            static constexpr auto DOT = make_constexpr_string(".");

            static constexpr auto SELECT = make_constexpr_string("SELECT");
            static constexpr auto FROM = make_constexpr_string("FROM");

            static constexpr auto NULL_STR = make_constexpr_string("NULL");
            static constexpr auto INTEGER = make_constexpr_string("INTEGER");
            static constexpr auto DOUBLE = make_constexpr_string("DOUBLE");
            static constexpr auto TEXT = make_constexpr_string("TEXT");
            static constexpr auto BLOB = make_constexpr_string("BLOB");

            static constexpr auto CURRENT_TIME = make_constexpr_string("CURRENT_TIME");
            static constexpr auto CURRENT_DATE = make_constexpr_string("CURRENT_DATE");
            static constexpr auto CURRENT_TIMESTAMP = make_constexpr_string("CURRENT_TIMESTAMP");
        };
    }
}