#pragma once

#include <tuple>
#include <utility>
#include <initializer_list>

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/column_set.hxx"
#include "sqlite3pp/sql/all.hxx"


namespace sqlite3pp {
    namespace sql {

        template<class T>
        struct table_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
            constexpr auto get_columns() const { return static_cast<const T *>(this)->get_columns(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

        template<class TableNameT, class ... Columns>
        class table_t : public table_base<table_t<TableNameT, Columns...>>, public Columns::template member_t<Columns>... {
        public:
            constexpr table_t(const detail::constexpr_string_base<TableNameT> &name, const column_base<Columns> &... columns)
                    : Columns::template member_t<Columns>{columns, }..., name{name}, columns{columns...} { }

            constexpr auto get_name() const { return name; }
            constexpr auto get_columns() const { return columns; }

            // Select
            constexpr auto select() const;
            constexpr auto select(all_t) const;

            template <class ... ColumnTypes>
            constexpr auto select(const column_base<ColumnTypes> & ... columns) const;

            // Insert

            // Update

            // Join

        private:
            const TableNameT name;
            const column_set<Columns...> columns;
        };

    }
}
