#pragma once

#include <tuple>
#include <type_traits>

#include "sqlite3pp/sql/expressions.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/table.hxx"


namespace sqlite3pp {
    namespace sql {

        // Forward Declarations.
        template <class ... ResultColumnT>
        class select_all;

        template <class ... ResultColumnT>
        class select_distinct;

        template <class SelectT, class TableT>
        class select_from;

        // Select base class
        template <class T>
        struct select_base {
            constexpr auto to_str() const { return static_cast<const T *>(this)->to_str(); }
        };

        // Members.
        struct select_all_member {
            template <class ... ResultColumnT>
            constexpr auto operator()(const expression<ResultColumnT> & ... result_columns) const {
                return select_all<ResultColumnT...>{result_columns...};
            }
        };

        struct select_distinct_member {
            template <class ... ResultColumnT>
            constexpr auto operator()(const expression<ResultColumnT> & ... result_columns) const {
                return select_distinct<ResultColumnT...>{result_columns...};
            }
        };

        template <class SelectT>
        class select_from_member {
        public:
            constexpr select_from_member(const select_base<SelectT> &select)
                : select{static_cast<const SelectT &>(select)} {}

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return select_from<SelectT, TableT>{select, table};
            }

        private:
            const SelectT &select;
        };

        template <class ... ResultColumnT>
        class select : public select_base<select<ResultColumnT...>> {
        public:
            constexpr select(const expression<ResultColumnT> & ... result_columns)
                    : FROM{*this}, result_columns{static_cast<const ResultColumnT &>(result_columns)...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        sql_strings::SELECT,
                        make_result_column_str(std::make_index_sequence<std::tuple_size<decltype(result_columns)>::value>())
                );
            }

            select_from_member<select<ResultColumnT...>> FROM;

        private:
            template <std::size_t ... Indexes>
            constexpr auto make_result_column_str(std::index_sequence<Indexes...>) const {
                return sql_strings::COMMA.join(std::get<Indexes>(result_columns).to_str()...);
            }

        private:
            std::tuple<const ResultColumnT & ...> result_columns;
        };

        template <class ... ResultColumnT>
        class select_all : public select_base<select_all<ResultColumnT...>> {
        public:
            constexpr select_all(const expression<ResultColumnT> & ... result_columns)
                : FROM{*this}, result_columns{static_cast<const ResultColumnT &>(result_columns)...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        sql_strings::SELECT,
                        sql_strings::ALL,
                        make_result_column_str(std::make_index_sequence<std::tuple_size<decltype(result_columns)>::value>())
                );
            }

            select_from_member<select_all<ResultColumnT...>> FROM;

        private:
            template <std::size_t ... Indexes>
            constexpr auto make_result_column_str(std::index_sequence<Indexes...>) const {
                return sql_strings::COMMA.join(std::get<Indexes>(result_columns).to_str()...);
            }

        private:
            std::tuple<const ResultColumnT & ...> result_columns;
        };

        template <class ... ResultColumnT>
        class select_distinct : public select_base<select_distinct<ResultColumnT...>> {
        public:
            constexpr select_distinct(const expression<ResultColumnT> & ... result_columns)
                : FROM{*this}, result_columns{static_cast<const ResultColumnT &>(result_columns)...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        sql_strings::SELECT,
                        sql_strings::DISTINCT,
                        make_result_column_str(std::make_index_sequence<std::tuple_size<decltype(result_columns)>::value>())
                );
            }

            select_from_member<select_distinct<ResultColumnT...>> FROM;

        private:
            template <std::size_t ... Indexes>
            constexpr auto make_result_column_str(std::index_sequence<Indexes...>) const {
                return sql_strings::COMMA.join(std::get<Indexes>(result_columns).to_str()...);
            }

        private:
            std::tuple<const ResultColumnT & ...> result_columns;
        };

        struct select_member {

            template <class ... ResultColumnT>
            constexpr auto operator()(const expression<ResultColumnT> & ... result_columns) const {
                return select<ResultColumnT...>{result_columns...};
            }

            select_all_member ALL;
            select_distinct_member DISTINCT;
        };

        template <class SelectT, class TableT>
        class select_from : public select_base<select_from<SelectT, TableT>> {
        public:
            constexpr select_from(const select_base<SelectT> &select, const table_base<TableT> &table)
                : select{static_cast<const SelectT &>(select)}, table{static_cast<const TableT &>(table)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        select.to_str(),
                        sql_strings::FROM,
                        table.get_name()
                );
            }

        private:
            const SelectT &select;
            const TableT &table;
        };

        class select_where : public select_base<select_where> {
        };
    }
}