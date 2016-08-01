#pragma once

namespace sqlitepp {

    template <typename CharT>
    class sql_str {
    public:
        constexpr sql_str(const CharT * str, std::size_t size) : str{str}, size{size} {}

    private:
        const CharT * str;
        const std::size_t size;
    };

    using sql_u8_str = sql_str<char>;
    using sql_u16_str = sql_str<char16_t>;

}

constexpr sqlitepp::sql_u8_str operator "" _sql_str(const char * str, std::size_t size) {
    return {str, size};
}

constexpr sqlitepp::sql_u16_str operator "" _sql_str(const char16_t * str, std::size_t size) {
    return {str, size};
}
