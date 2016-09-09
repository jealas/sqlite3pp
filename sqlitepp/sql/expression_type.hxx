#pragma once

namespace sqlitepp {
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