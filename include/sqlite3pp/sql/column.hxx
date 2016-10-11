#pragma once

#include <type_traits>

#include "sqlite3pp/detail/constexpr_string.hxx"
#include "sqlite3pp/sql/column_type.hxx"
#include "sqlite3pp/sql/serializable.hxx"


namespace sqlite3pp {
    namespace sql {

        template<class T>
        struct column_base : public serializable<T> {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
            constexpr column_type get_type() const { return static_cast<const T *>(this)->get_type(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

        template<template <class> class MemberT, column_type ColumnType, class NameType>
        class column_t : public column_base<column_t<MemberT, ColumnType, NameType>> {
        public:
            template <class T>
            using member_t = MemberT<T>;

            explicit constexpr column_t(const detail::constexpr_string_base<NameType> &name) : name{name} { }

            constexpr auto to_str() const { return name; }

            constexpr auto get_name() const { return name; }
            constexpr column_type get_type() const { return ColumnType; }

        private:
            NameType name;
        };

        template <template <class> class MemberT, column_type ColumnType, std::size_t NameLength>
        constexpr auto column(const char (&name)[NameLength]) {
            auto name_str = detail::make_constexpr_string(name);

            return column_t<MemberT, ColumnType, decltype(name_str)>{name_str};
        }

    }
}
