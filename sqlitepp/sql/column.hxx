#pragma once

#include <type_traits>

#include "sqlitepp/sql/column_type.hxx"
#include "sqlitepp/detail/constexpr_string.hxx"

namespace sqlitepp {
    namespace sql {

        template<class T>
        struct column_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }

            constexpr sql::column_type get_type() const { return static_cast<const T *>(this)->get_type(); }

            constexpr operator T() const { return *static_cast<const T *>(this); }
        };

        template<class CharT, class NameType>
        class column_t : public column_base<column_t<CharT, NameType>> {
        public:
            explicit constexpr column_t(const detail::constexpr_string_base<NameType> &name,
                                        sql::column_type column_type) : name{name}, column_type{column_type} { }

            constexpr auto get_name() const { return name; }

            constexpr auto get_type() const { return column_type; }

        private:
            const NameType name;
            const sql::column_type column_type;
        };

        template<std::size_t NameLength>
        constexpr auto column(const char (&name)[NameLength], sql::column_type column_type) {
            auto name_str = detail::make_constexpr_string(name);

            return column_t<char, decltype(name_str)>(name_str, column_type);
        }

        template<std::size_t NameLength>
        constexpr auto column(const char16_t (&name)[NameLength], sql::column_type column_type) {
            auto name_str = detail::make_constexpr_string(name);

            return column_t<char16_t, decltype(name_str)>(name_str, column_type);
        }

    }
}
