#pragma once


namespace sqlite3pp {
    namespace sql {

        enum class expression_type {
            NULL_T,
            ANY,
            BOOL,
            INT,
            REAL,
            TEXT
        };

    }
}