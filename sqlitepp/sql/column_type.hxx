#pragma once

#include <cstdint>

namespace sqlitepp {
    namespace sql {

        enum class column_type : std::uint8_t {
            INTEGER,
            BLOB,
            REAL,
            TEXT,
            TEXT16
        };

        constexpr auto INTEGER = column_type::INTEGER;
        constexpr auto BLOB = column_type::BLOB;
        constexpr auto REAL = column_type::REAL;
        constexpr auto TEXT = column_type::TEXT;
        constexpr auto TEXT16 = column_type::TEXT16;

    }
}