#pragma once

namespace sqlitepp {
    namespace sql {

        class str {
        public:
            constexpr str(const char *c_str, std::size_t size) : c_str{c_str}, size{size} {}

        private:
            const char * c_str;
            const std::size_t size;
        };

    }
}

constexpr sqlitepp::sql::str operator "" _sql_str(const char * str, std::size_t size) {
    return {str, size};
}
