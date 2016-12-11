#pragma once

#include <type_traits>

#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/table.hxx"
#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/expressions.hxx"


namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct insert_base {
            constexpr auto serialize() const { return static_cast<const T *>(this)->to_str(); }
        };

        template <class T>
        struct insert_syntax_base {
            constexpr auto to_str() const { return static_cast<const T *>(this)->to_str(); }
        };

        // Forward declarations.
        template <class InsertT>
        class insert_or_replace_member;

        template <class InsertT>
        class insert_or_rollback_member;

        template <class InsertT>
        class insert_or_abort_member;

        template <class InsertT>
        class insert_or_fail_member;

        template <class InsertT>
        class insert_or_ignore_member;

        template <class InsertSyntaxT>
        class insert_into_member;

        // TODO: Implement the replace clause.

        template <class InsertSyntaxT>
        class insert_or_member : public insert_syntax_base<insert_or_member<InsertSyntaxT>> {
        public:
            constexpr insert_or_member(const insert_syntax_base<InsertSyntaxT> &insert)
                : REPLACE{*this},
                  ROLLBACK{*this},
                  ABORT{*this},
                  FAIL{*this},
                  IGNORE{*this},
                  insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    sql_strings::OR
                );
            }

            insert_or_replace_member<insert_or_member<InsertSyntaxT>> REPLACE;
            insert_or_rollback_member<insert_or_member<InsertSyntaxT>> ROLLBACK;
            insert_or_abort_member<insert_or_member<InsertSyntaxT>> ABORT;
            insert_or_fail_member<insert_or_member<InsertSyntaxT>> FAIL;
            insert_or_ignore_member<insert_or_member<InsertSyntaxT>> IGNORE;

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT>
        class insert_or_replace_member : public insert_syntax_base<insert_or_replace_member<InsertSyntaxT>> {
        public:
            constexpr insert_or_replace_member(const insert_syntax_base<InsertSyntaxT> &insert)
                : INTO{*this}, insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    sql_strings::REPLACE
                );
            }

            insert_into_member<insert_or_replace_member<InsertSyntaxT>> INTO;

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT>
        class insert_or_rollback_member  : public insert_syntax_base<insert_or_rollback_member<InsertSyntaxT>> {
        public:
            constexpr insert_or_rollback_member(const insert_syntax_base<InsertSyntaxT> &insert)
                : INTO{*this}, insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    sql_strings::ROLLBACK
                );
            }

            insert_into_member<insert_or_rollback_member<InsertSyntaxT>> INTO;

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT>
        class insert_or_abort_member  : public insert_syntax_base<insert_or_abort_member<InsertSyntaxT>> {
        public:
            constexpr insert_or_abort_member(const insert_syntax_base<InsertSyntaxT> &insert)
                    : INTO{*this}, insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                    return sql_strings::SPACE.join(
                            insert.to_str(),
                            sql_strings::ABORT
                    );
            }

            insert_into_member<insert_or_abort_member<InsertSyntaxT>> INTO;

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT>
        class insert_or_fail_member  : public insert_syntax_base<insert_or_fail_member<InsertSyntaxT>> {
        public:
            constexpr insert_or_fail_member(const insert_syntax_base<InsertSyntaxT> &insert)
                    : INTO{*this}, insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        insert.to_str(),
                        sql_strings::FAIL
                );
            }

            insert_into_member<insert_or_fail_member<InsertSyntaxT>> INTO;

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT>
        class insert_or_ignore_member  : public insert_syntax_base<insert_or_ignore_member<InsertSyntaxT>> {
        public:
            constexpr insert_or_ignore_member(const insert_syntax_base<InsertSyntaxT> &insert)
                    : INTO{*this}, insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        insert.to_str(),
                        sql_strings::IGNORE
                );
            }

            insert_into_member<insert_or_ignore_member<InsertSyntaxT>> INTO;

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT, class ... ExpressionT>
        class insert_into_values : public insert_base<insert_into_values<InsertSyntaxT, ExpressionT...>> {
        public:
            constexpr insert_into_values(const insert_syntax_base<InsertSyntaxT> &insert, const expression<ExpressionT> & ... expressions)
                : insert{static_cast<const InsertSyntaxT &>(insert)}, expressions{static_cast<const ExpressionT &>(expressions)...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    join_constexpr_strings(sql_strings::OPEN_PARENTHESIS,
                                           make_expressions_str(std::make_index_sequence<sizeof...(ExpressionT)>()),
                                           sql_strings::CLOSE_PARENTHESIS)
                );
            }

        private:
            template <std::size_t ... Indexes>
            constexpr auto make_expressions_str(std::index_sequence<Indexes...>) const {
                return sql_strings::COMMA.join(std::get<Indexes>(expressions).to_str()...);
            }

        private:
            const InsertSyntaxT &insert;
            std::tuple<ExpressionT...> expressions;
        };

        template <class InsertSyntaxT>
        class insert_into_values_member : public insert_syntax_base<insert_into_values_member<InsertSyntaxT>> {
        public:
            constexpr insert_into_values_member(const insert_syntax_base<InsertSyntaxT> &insert)
                : insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    sql_strings::VALUES
                );
            }

            template <class ... ExpressionT>
            constexpr auto operator()(const expression<ExpressionT> & ... expressions) const {
                return insert_into_values<insert_into_values_member<InsertSyntaxT>, ExpressionT...>{*this, expressions...};
            }

        private:
            const InsertSyntaxT &insert;
        };

        template <class InsertSyntaxT, class ... ColumnT>
        class insert_into_columns : public insert_syntax_base<insert_into_columns<InsertSyntaxT, ColumnT...>> {
        public:
            constexpr insert_into_columns(const insert_syntax_base<InsertSyntaxT> &insert, const column_base<ColumnT> & ... columns)
                : VALUES{*this}, insert{static_cast<const InsertSyntaxT &>(insert)}, columns{static_cast<const ColumnT &>(columns)...} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        insert.to_str(),
                        join_constexpr_strings(sql_strings::OPEN_PARENTHESIS,
                                               make_columns_str(std::make_index_sequence<sizeof...(ColumnT)>()),
                                               sql_strings::CLOSE_PARENTHESIS)
                );
            }

            insert_into_values_member<insert_into_columns<InsertSyntaxT, ColumnT...>> VALUES;

        private:
            template <std::size_t ... Indexes>
            constexpr auto make_columns_str(std::index_sequence<Indexes...>) const {
                return sql_strings::COMMA.join(std::get<Indexes>(columns).to_str()...);
            }

        private:
            const InsertSyntaxT &insert;
            std::tuple<const ColumnT & ...> columns;
        };

        template <class InsertSyntaxT, class TableT>
        class insert_into_table : public insert_syntax_base<insert_into_table<InsertSyntaxT, TableT>> {
        public:
            constexpr insert_into_table(const insert_syntax_base<InsertSyntaxT> &insert, const table_base<TableT> &table)
                : VALUES{*this}, insert{static_cast<const InsertSyntaxT &>(insert)}, table{static_cast<const TableT &>(table)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    table.get_name()
                );
            }

            template <class ... ColumnT>
            constexpr auto operator()(const column_base<ColumnT> & ... columns) const {
                return insert_into_columns<insert_into_table<InsertSyntaxT, TableT>, ColumnT...>{*this, columns...};
            }

            insert_into_values_member<insert_into_table<InsertSyntaxT, TableT>> VALUES;

        private:
            const InsertSyntaxT &insert;
            const TableT &table;
        };

        template <class InsertSyntaxT>
        class insert_into_member : public insert_syntax_base<insert_into_member<InsertSyntaxT>> {
        public:
            constexpr insert_into_member(const insert_syntax_base<InsertSyntaxT> &insert)
                : insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    sql_strings::INTO
                );
            }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return insert_into_table<insert_into_member<InsertSyntaxT>, TableT>{*this, table};
            }

        private:
            const InsertSyntaxT &insert;
        };

        struct insert_member : public insert_syntax_base<insert_member> {
            constexpr insert_member() : OR{*this}, INTO{*this} {}

            constexpr auto to_str() const { return sql_strings::INSERT; }

            insert_or_member<insert_member> OR;
            insert_into_member<insert_member> INTO;
        };

    }
}