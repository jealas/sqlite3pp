#pragma once

namespace sqlitepp {

    class sql_str {
    public:
        constexpr sql_str(const char * str, std::size_t size) : str{str}, size{size} {}

    private:
        const char * str;
        const std::size_t size;
    };

}

constexpr sqlitepp::sql_str operator "" _sql_str(const char * str, std::size_t size) {
    return {str, size};
}
