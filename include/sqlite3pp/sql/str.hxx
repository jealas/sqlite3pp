#pragma once


namespace sqlite3pp {
    namespace sql {

        class str;
        constexpr str operator ""_sql_str(const char *, std::size_t);

        class str {
            friend constexpr str operator ""_sql_str(const char *, std::size_t);

        public:
            constexpr const char * c_str() const { return c_str_ptr; }
            constexpr std::size_t length() const { return size; }

        private:
            constexpr str(const char *c_str_ptr, std::size_t size) : c_str_ptr{c_str_ptr}, size{size} {}

        private:
            const char * c_str_ptr;
            const std::size_t size;
        };

        constexpr str operator ""_sql_str(const char * str, std::size_t size) {
            return {str, size};
        }
    }
}
