#pragma once

#include <tuple>
#include <utility>
#include <initializer_list>

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"


namespace sqlite3pp {
    namespace sql {

        template<class T>
        struct table_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
        };

        template<template <class ...> class TableT, class TableNameT, class ... ColumnT>
        class table_t : public TableT<fully_qualified_column_t<TableNameT, ColumnT>...>, public table_base<table_t<TableT, TableNameT, ColumnT...>> {
        public:
            constexpr table_t(const detail::constexpr_string_base<TableNameT> &name, const column_base<ColumnT> & ... columns)
                : TableT<fully_qualified_column_t<TableNameT, ColumnT>...>{fully_qualified_column_t<TableNameT, ColumnT>{__name, columns}...}, __name{name} { }

            constexpr auto get_name() const { return __name; }

        private:
            TableNameT __name;
        };

    }
}
