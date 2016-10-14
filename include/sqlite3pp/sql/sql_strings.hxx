#pragma once

#include "sqlite3pp/detail/constexpr_string.hxx"


namespace {
    using namespace sqlite3pp::detail;
}

namespace sqlite3pp {
    namespace sql {

        struct sql_strings {
            static constexpr auto COMMA = make_constexpr_string(",");
            static constexpr auto SPACE = make_constexpr_string(" ");
            static constexpr auto QUESTION_MARK = make_constexpr_string("?");
            static constexpr auto DOT = make_constexpr_string(".");
            static constexpr auto SINGLE_QUOTE = make_constexpr_string("'");
            static constexpr auto DOUBLE_QUOTE = make_constexpr_string("\"");
            static constexpr auto OPEN_PARENTHESIS = make_constexpr_string("(");
            static constexpr auto CLOSE_PARENTHESIS = make_constexpr_string(")");
            static constexpr auto UNDERSCORE = make_constexpr_string("_");

            static constexpr auto PIPE_PIPE = make_constexpr_string("||");
            static constexpr auto ASTERISK = make_constexpr_string("*");
            static constexpr auto FORWARD_SLASH = make_constexpr_string("/");
            static constexpr auto PERCENT = make_constexpr_string("%");
            static constexpr auto PLUS = make_constexpr_string("+");
            static constexpr auto MINUS = make_constexpr_string("-");
            static constexpr auto LEFT_SHIFT = make_constexpr_string("<<");
            static constexpr auto RIGHT_SHIFT = make_constexpr_string(">>");
            static constexpr auto AMPERSAND = make_constexpr_string("&");
            static constexpr auto PIPE = make_constexpr_string("|");
            static constexpr auto LESS_THAN = make_constexpr_string("<");
            static constexpr auto GREATER_THAN = make_constexpr_string(">");
            static constexpr auto LESS_EQUALS = make_constexpr_string("<=");
            static constexpr auto GREATER_EQUALS = make_constexpr_string(">=");
            static constexpr auto EQUALS = make_constexpr_string("=");
            static constexpr auto EQUALS_EQUALS = make_constexpr_string("==");
            static constexpr auto NOT_EQUALS = make_constexpr_string("!=");
            static constexpr auto LESS_GREATER = make_constexpr_string("<>");
            static constexpr auto TILDE = make_constexpr_string("~");

            static constexpr auto CAST = make_constexpr_string("CAST");
            static constexpr auto AS = make_constexpr_string("AS");
            static constexpr auto IS = make_constexpr_string("IS");
            static constexpr auto IS_NOT = make_constexpr_string("IS NOT");
            static constexpr auto IN = make_constexpr_string("IN");
            static constexpr auto LIKE = make_constexpr_string("LIKE");
            static constexpr auto GLOB = make_constexpr_string("GLOB");
            static constexpr auto MATCH = make_constexpr_string("MATCH");
            static constexpr auto REGEXP = make_constexpr_string("REGEXP");
            static constexpr auto BETWEEN = make_constexpr_string("BETWEEN");
            static constexpr auto AND = make_constexpr_string("AND");
            static constexpr auto OR = make_constexpr_string("OR");
            static constexpr auto NOT = make_constexpr_string("NOT");
            static constexpr auto ABS = make_constexpr_string("ABS");

            static constexpr auto NOT_LIKE = make_constexpr_string("NOT LIKE");
            static constexpr auto NOT_GLOB = make_constexpr_string("NOT GLOB");
            static constexpr auto NOT_MATCH = make_constexpr_string("NOT MATCH");
            static constexpr auto NOT_REGEXP = make_constexpr_string("NOT REGEXP");
            static constexpr auto NOT_BETWEEN = make_constexpr_string("NOT BETWEEN");

            static constexpr auto SELECT = make_constexpr_string("SELECT");
            static constexpr auto FROM = make_constexpr_string("FROM");

            static constexpr auto NULL_STR = make_constexpr_string("NULL");
            static constexpr auto INTEGER = make_constexpr_string("INTEGER");
            static constexpr auto INT = make_constexpr_string("INT");
            static constexpr auto REAL = make_constexpr_string("REAL");
            static constexpr auto DOUBLE = make_constexpr_string("DOUBLE");
            static constexpr auto FLOAT = make_constexpr_string("FLOAT");
            static constexpr auto TEXT = make_constexpr_string("TEXT");
            static constexpr auto CHAR = make_constexpr_string("CHAR");
            static constexpr auto CLOB = make_constexpr_string("CLOB");
            static constexpr auto VARCHAR = make_constexpr_string("VARCHAR");
            static constexpr auto BLOB = make_constexpr_string("BLOB");
            static constexpr auto NUMERIC = make_constexpr_string("NUMERIC");
            static constexpr auto DECIMAL = make_constexpr_string("DECIMAL");
            static constexpr auto BOOLEAN = make_constexpr_string("BOOLEAN");
            static constexpr auto DATE = make_constexpr_string("DATE");
            static constexpr auto DATETIME = make_constexpr_string("DATETIME");

            static constexpr auto CURRENT_TIME = make_constexpr_string("CURRENT_TIME");
            static constexpr auto CURRENT_DATE = make_constexpr_string("CURRENT_DATE");
            static constexpr auto CURRENT_TIMESTAMP = make_constexpr_string("CURRENT_TIMESTAMP");
        };

    }
}
