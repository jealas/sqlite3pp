#pragma once

#include <type_traits>

#include "sqlite3pp/detail/constexpr_string.hxx"
#include "sqlite3pp/sql/column_type.hxx"
#include "sqlite3pp/sql/expressions.hxx"


namespace sqlite3pp {
    namespace sql {

        template<class T>
        struct column_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
            constexpr column_type get_type() const { return static_cast<const T *>(this)->get_type(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

        template <class T>
        struct column_expression;

        template <class ColumnExpressionT>
        class desc_expression_member {
        public:
            constexpr desc_expression_member(const column_expression<ColumnExpressionT> &column_expression)
                : column_expression{static_cast<const ColumnExpressionT &>(column_expression)} {}

            constexpr auto operator()() const {
                return desc_expression<ColumnExpressionT>{column_expression};
            }

        private:
            const ColumnExpressionT &column_expression;
        };

        template <class ColumnExpressionT>
        class asc_expression_member {
        public:
            constexpr asc_expression_member(const column_expression<ColumnExpressionT> &column_expression)
                    : column_expression{static_cast<const ColumnExpressionT &>(column_expression)} {}

            constexpr auto operator()() const {
                return asc_expression<ColumnExpressionT>{column_expression};
            }

        private:
            const ColumnExpressionT &column_expression;
        };

        template <class T>
        struct column_expression : public expression<T>, public column_base<T> {
            desc_expression_member<T> DESC{*this};
            asc_expression_member<T> ASC{*this};
        };

        template<template <class> class MemberT, column_type ColumnType, class NameType>
        class column_t : public column_expression<column_t<MemberT, ColumnType, NameType>> {
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

    }
}
