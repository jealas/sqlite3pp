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
            static constexpr auto COUNT = make_constexpr_string("COUNT");

            static constexpr auto NOT_LIKE = make_constexpr_string("NOT LIKE");
            static constexpr auto NOT_GLOB = make_constexpr_string("NOT GLOB");
            static constexpr auto NOT_MATCH = make_constexpr_string("NOT MATCH");
            static constexpr auto NOT_REGEXP = make_constexpr_string("NOT REGEXP");
            static constexpr auto NOT_BETWEEN = make_constexpr_string("NOT BETWEEN");

            static constexpr auto SELECT = make_constexpr_string("SELECT");
            static constexpr auto FROM = make_constexpr_string("FROM");
            static constexpr auto ALL = make_constexpr_string("ALL");
            static constexpr auto DISTINCT = make_constexpr_string("DISTINCT");
            static constexpr auto WHERE = make_constexpr_string("WHERE");
            static constexpr auto GROUP = make_constexpr_string("GROUP");
            static constexpr auto BY = make_constexpr_string("BY");
            static constexpr auto HAVING = make_constexpr_string("HAVING");
            static constexpr auto ORDER = make_constexpr_string("ORDER");
            static constexpr auto LIMIT = make_constexpr_string("LIMIT");
            static constexpr auto OFFSET = make_constexpr_string("OFFSET");
            static constexpr auto ASC = make_constexpr_string("ASC");
            static constexpr auto DESC = make_constexpr_string("DESC");
            static constexpr auto COLLATE = make_constexpr_string("COLLATE");
            static constexpr auto BYTE = make_constexpr_string("BYTE");
            static constexpr auto NOCASE = make_constexpr_string("NOCASE");
            static constexpr auto RTRIM = make_constexpr_string("RTRIM");

            static constexpr auto INSERT = make_constexpr_string("INSERT");
            static constexpr auto INTO = make_constexpr_string("INTO");
            static constexpr auto REPLACE = make_constexpr_string("REPLACE");
            static constexpr auto ROLLBACK = make_constexpr_string("ROLLBACK");
            static constexpr auto ABORT = make_constexpr_string("ABORT");
            static constexpr auto FAIL = make_constexpr_string("FAIL");
            static constexpr auto IGNORE = make_constexpr_string("IGNORE");
            static constexpr auto VALUES = make_constexpr_string("VALUES");
            static constexpr auto DEFAULT = make_constexpr_string("DEFAULT");

            static constexpr auto CREATE = make_constexpr_string("CREATE");
            static constexpr auto TEMPORARY = make_constexpr_string("TEMPORARY");
            static constexpr auto TEMP = make_constexpr_string("TEMP");
            static constexpr auto TABLE = make_constexpr_string("TABLE");

            static constexpr auto NULL_STR = make_constexpr_string("NULL");

            static constexpr auto INTEGER = make_constexpr_string("INTEGER");
            static constexpr auto INT = make_constexpr_string("INT");
            static constexpr auto TINYINT = make_constexpr_string("TINYINT");
            static constexpr auto SMALLINT = make_constexpr_string("SMALLINT");
            static constexpr auto MEDIUMINT = make_constexpr_string("MEDIUMINT");
            static constexpr auto BIGINT = make_constexpr_string("BIGINT");

            static constexpr auto REAL = make_constexpr_string("REAL");
            static constexpr auto DOUBLE = make_constexpr_string("DOUBLE");
            static constexpr auto FLOAT = make_constexpr_string("FLOAT");

            static constexpr auto TEXT = make_constexpr_string("TEXT");
            static constexpr auto CHAR = make_constexpr_string("CHAR");
            static constexpr auto CLOB = make_constexpr_string("CLOB");
            static constexpr auto VARCHAR = make_constexpr_string("VARCHAR");
            static constexpr auto CHARACTER = make_constexpr_string("CHARACTER");
            static constexpr auto NCHAR = make_constexpr_string("NCHAR");
            static constexpr auto NVARCHAR = make_constexpr_string("NVARCHAR");

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
