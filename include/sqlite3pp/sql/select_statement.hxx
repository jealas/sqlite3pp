#pragma once

#include <tuple>
#include <type_traits>

#include "sqlite3pp/sql/expressions.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/table.hxx"


namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct select_base {
            constexpr auto to_str() const { return static_cast<const T *>(this)->to_str(); }
        };

        // Forward Declarations.
        template <class ... ResultColumnT>
        class select_all;

        template <class ... ResultColumnT>
        class select_distinct;

        template <class SelectT, class TableT>
        class select_from;

        template <class SelectT, class ExpressionT>
        class select_where;

        template <class SelectT>
        class select_group;

        template <class SelectT, class ... ExpressionT>
        class select_group_by;

        template <class SelectT, class ExpressionT>
        class select_having;

        template <class SelectT, class ... ExpressionT>
        class select_order_by {
        public:
            constexpr select_order_by(const select_base<SelectT> &select, const expression<ExpressionT> & ... expressions)
                : select{static_cast<const SelectT &>(select)}, expressions{static_cast<const ExpressionT &>(expressions)...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        select.to_str(),
                        sql_strings::ORDER,
                        sql_strings::BY,
                        make_expression_str(std::make_index_sequence<sizeof...(ExpressionT)>())
                );
            }

        private:
            template <std::size_t ... ExpressionIndex>
            constexpr auto make_expression_str(std::index_sequence<ExpressionIndex...>) const {
                return sql_strings::COMMA.join(std::get<ExpressionIndex>(expressions).to_str()...);
            }

        private:
            const SelectT &select;
            std::tuple<const ExpressionT &...> expressions;
        };

        template <class SelectT>
        class select_order_by_member {
        public:
            constexpr select_order_by_member(const select_base<SelectT> &select)
                : select{static_cast<const SelectT &>(select)} {}

            template <class ... ExpressionT>
            constexpr auto operator()(const expression<ExpressionT> & ... expressions) const {
                return select_order_by<SelectT, ExpressionT...>{select, expressions...};
            }

        private:
            const SelectT &select;
        };

        template <class SelectT>
        class select_order_member {
        public:
            constexpr select_order_member(const select_base<SelectT> &select)
                : BY{select}, select{static_cast<const SelectT &>(select)} {}

            select_order_by_member<SelectT> BY;

        private:
            const SelectT &select;
        };

        template <class SelectT>
        struct select_core : public select_base<SelectT> {
            select_order_member<SelectT> ORDER{*this};
        };

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

        template <class SelectT>
        class select_where_member {
        public:
            constexpr select_where_member(const select_base<SelectT> &select)
                : select{static_cast<const SelectT &>(select)} {}

            template <class ExpressionT>
            constexpr auto operator()(const expression<ExpressionT> &expression) const {
                return select_where<SelectT, ExpressionT>{select, expression};
            }

        private:
            const SelectT &select;
        };

        template <class SelectT>
        class select_group_by_member {
        public:
            constexpr select_group_by_member(const select_base<SelectT> &select)
                : select{static_cast<const SelectT &>(select)} {}

            template <class ... ExpressionT>
            constexpr auto operator()(const expression<ExpressionT> & ... expressions) const {
                return select_group_by<SelectT, ExpressionT...>{select, expressions...};
            }

        private:
            const SelectT &select;
        };

        template <class SelectT>
        class select_group_member {
        public:
            constexpr select_group_member(const select_base<SelectT> &select)
                : BY{select}, select{static_cast<const SelectT &>(select)} {}

            select_group_by_member<SelectT> BY;

        private:
            const SelectT &select;
        };

        template <class SelectT>
        class select_having_member {
        public:
            constexpr select_having_member(const select_base<SelectT> &select)
                : select{static_cast<const SelectT &>(select)} {}

            template <class ExpressionT>
            constexpr auto operator()(const expression<ExpressionT> &expression) const {
                return select_having<SelectT, ExpressionT>{select, expression};
            }

        private:
            const SelectT &select;
        };

        template <class ... ResultColumnT>
        class select : public select_core<select<ResultColumnT...>> {
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
        class select_all : public select_core<select_all<ResultColumnT...>> {
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
        class select_distinct : public select_core<select_distinct<ResultColumnT...>> {
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
        class select_from : public select_core<select_from<SelectT, TableT>> {
        public:
            constexpr select_from(const select_base<SelectT> &select, const table_base<TableT> &table)
                : WHERE{*this}, GROUP{*this}, select{static_cast<const SelectT &>(select)}, table{static_cast<const TableT &>(table)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        select.to_str(),
                        sql_strings::FROM,
                        table.get_name()
                );
            }

            select_where_member<select_from<SelectT, TableT>> WHERE;
            select_group_member<select_from<SelectT, TableT>> GROUP;

        private:
            const SelectT &select;
            const TableT &table;
        };

        template <class SelectT, class ExpressionT>
        class select_where : public select_core<select_where<SelectT, ExpressionT>> {
        public:
            constexpr select_where(const select_base<SelectT> &select, const expression<ExpressionT> &expression)
                : GROUP{*this}, select{static_cast<const SelectT &>(select)}, expression{static_cast<const ExpressionT &>(expression)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        select.to_str(),
                        sql_strings::WHERE,
                        expression.to_str()
                );
            }

            select_group_member<select_where<SelectT, ExpressionT>> GROUP;

        private:
            const SelectT &select;
            const ExpressionT &expression;
        };

        template <class SelectT, class ... ExpressionT>
        class select_group_by : public select_core<select_group_by<SelectT, ExpressionT...>> {
        public:
            constexpr select_group_by(const select_base<SelectT> &select, const expression<ExpressionT> & ... expressions)
                : HAVING{*this}, select{static_cast<const SelectT &>(select)}, expressions{expressions...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        select.to_str(),
                        sql_strings::GROUP,
                        sql_strings::BY,
                        make_expression_str(std::make_index_sequence<std::tuple_size<decltype(expressions)>::value>())
                );
            }

            select_having_member<select_group_by<SelectT, ExpressionT...>> HAVING;

        private:
            template <std::size_t ... ExpressionIndex>
            constexpr auto make_expression_str(std::index_sequence<ExpressionIndex...>) const {
                return sql_strings::COMMA.join(std::get<ExpressionIndex>(expressions).to_str()...);
            }

        private:
            const SelectT &select;
            std::tuple<const ExpressionT & ...> expressions;
        };

        template <class SelectT, class ExpressionT>
        class select_having : public select_core<select_having<SelectT, ExpressionT>> {
        public:
            constexpr select_having(const select_base<SelectT> &select, const expression<ExpressionT> &expression)
                : select{static_cast<const SelectT &>(select)}, expression{static_cast<const ExpressionT &>(expression)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        select.to_str(),
                        sql_strings::HAVING,
                        expression.to_str()
                );
            }

        private:
            const SelectT &select;
            const ExpressionT &expression;
        };
    }
}