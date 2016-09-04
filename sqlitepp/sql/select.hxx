#pragma once

#include <tuple>
#include <initializer_list>

#include "sqlitepp/sql/from.hxx"
#include "sqlitepp/sql/all.hxx"
#include "sqlitepp/sql/column.hxx"


namespace sqlitepp {
    namespace sql {

        template <class T>
        struct select_base {
        };

        template <class Table, class ... ColumnTypes>
        class select_t : public select_base<select_t<Table, ColumnTypes...>> {
        public:
            constexpr select_t(const table_base<Table> & table, const column_base<ColumnTypes> & ... selected_columns)
                    : table{table}, selected_columns{selected_columns...} {

                for (auto col : std::initializer_list<column_view>{selected_columns...}) {
                    if (!table.get_columns().has_column(col)) {
                        throw "The selected columns must be members of the table.";
                    }
                }
            }

        private:
            const Table table;
            const std::tuple<ColumnTypes ...> selected_columns;
        };

        template <class TableT>
        class select_all_t : public select_base<select_all_t<TableT>> {
        public:
            explicit constexpr select_all_t(const table_base<TableT> & table) : table{table} {}

        private:
            const TableT table;
        };

        template <class TableT, class ... Columns>
        constexpr auto select(const from_table_t<TableT> &from_table, const Columns & ... columns) {
            return select_t<TableT, Columns...>{from_table.get_table(), columns...};
        }

        template <class TableT>
        constexpr auto select(const from_table_t<TableT> &table, all_t) {
            return select_all_t<TableT>{table};
        }

        template <class TableT>
        constexpr auto select(const from_table_t<TableT> &table) { return select(table, all); }

    }
}
