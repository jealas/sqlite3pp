#pragma once

#include "sqlitepp/sql/column_view.hxx"


namespace sqlitepp {
    namespace sql {

        template <class ... ColumnTypes>
        class column_set {
        public:
            constexpr column_set(const column_base<ColumnTypes> & ... columns) : columns{columns...} {}

            constexpr std::size_t num_columns() const { return std::tuple_size<decltype(columns)>::value; }

            constexpr bool has_column(const column_view & column) const {
                return has_column_impl(column, std::make_index_sequence<std::tuple_size<decltype(columns)>::value>());
            }

        private:
            template <std::size_t ... TupleIndexes>
            constexpr bool has_column_impl(const column_view & column, std::index_sequence<TupleIndexes...>) const {
                for (const auto & col : std::initializer_list<column_view>{std::get<TupleIndexes>(columns)...}) {
                    if (col == column) {
                        return true;
                    }
                }

                return false;
            }

        private:
            const std::tuple<ColumnTypes ...> columns;
        };

    }
}