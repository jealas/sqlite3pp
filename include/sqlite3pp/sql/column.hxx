#pragma once

#include <type_traits>

#include "sqlite3pp/detail/constexpr_string.hxx"
#include "sqlite3pp/sql/expressions.hxx"


namespace sqlite3pp {
    namespace sql {

        template<class T>
        struct column_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
            constexpr auto get_type() const { return static_cast<const T *>(this)->get_type(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

        template <class T>
        struct column_expression;

        template <class ColumnEqualsT>
        struct column_equals_statement_base {
            constexpr auto to_str() const { return static_cast<const ColumnEqualsT *>(this)->to_str(); }
        };

        template <class ... ColumnT>
        class column_comma_list;

        template <class ColumnListT, class ExpressionT>
        class column_comma_list_equals_expression;

        template <class ColumnT, class ExpressionT>
        struct column_equals_expression;

        template <class CollateTypeT>
        struct collate_type;

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

        template <class ColumnExpressionT, class CollateTypeT>
        class column_collate : public column_expression<column_collate<ColumnExpressionT, CollateTypeT>> {
        public:
            constexpr column_collate(const column_expression<ColumnExpressionT> &column_expression, const collate_type<CollateTypeT> &collate_type)
                : column_expression{static_cast<const ColumnExpressionT &>(column_expression)}, collate_type{static_cast<const CollateTypeT &>(collate_type)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                        column_expression.to_str(),
                        sql_strings::COLLATE,
                        collate_type.get_name()
                );
            }

        private:
            const ColumnExpressionT &column_expression;
            const CollateTypeT &collate_type;
        };

        template <class T>
        struct collate_type {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
        };

        struct collate_byte : public collate_type<collate_byte> {
            constexpr auto get_name() const { return sql_strings::BYTE; }
        };

        struct collate_nocase : public collate_type<collate_nocase> {
            constexpr auto get_name() const { return sql_strings::NOCASE; }
        };

        struct collate_rtrim : public collate_type<collate_rtrim> {
            constexpr auto get_name() const { return sql_strings::RTRIM; }
        };

        template <std::size_t CustomCollationNameLength>
        class collate_custom : public collate_type<collate_custom<CustomCollationNameLength>> {
        public:
            constexpr collate_custom(const constexpr_string<CustomCollationNameLength> &collation_name)
                : collation_name{collation_name} {}

            constexpr auto get_name() const { return collation_name; }

        private:
            constexpr_string<CustomCollationNameLength> collation_name;
        };

        template <std::size_t CustomCollationNameLength>
        constexpr auto make_custom_collation(const char (&collation_name)[CustomCollationNameLength]) {
            return collate_custom<CustomCollationNameLength - 1u>{collation_name};
        }

        template <class ColumnExpressionT>
        class collate_expression_member {
        public:
            constexpr collate_expression_member(const column_expression<ColumnExpressionT> &column_expression)
                : column_expression{static_cast<const ColumnExpressionT &>(column_expression)} {}

            template <class CollateTypeT>
            constexpr auto operator()(const collate_type<CollateTypeT> &collate_type) const {
                return column_collate<ColumnExpressionT, CollateTypeT>{column_expression, collate_type};
            }

        private:
            const ColumnExpressionT &column_expression;
        };

        template <class ColumnExpressionT>
        struct column_expression : public expression<ColumnExpressionT>, public column_base<ColumnExpressionT> {
            desc_expression_member<ColumnExpressionT> DESC{*this};
            asc_expression_member<ColumnExpressionT> ASC{*this};
        };

        template <class TableNameT, class ColumnT>
        class fully_qualified_column_t : public column_expression<fully_qualified_column_t<TableNameT, ColumnT>> {
        public:
            constexpr fully_qualified_column_t(const detail::constexpr_string_base<TableNameT> &table_name, const column_base<ColumnT> &column)
                    : COLLATE{*this}, table_name{static_cast<const TableNameT &>(table_name)}, column{static_cast<const ColumnT &>(column)} {}

            constexpr auto to_str() const {
                return sql_strings::DOT.join(
                    table_name,
                    column.get_name()
                );
            }

            collate_expression_member<fully_qualified_column_t<TableNameT, ColumnT>> COLLATE;

        private:
            const TableNameT &table_name;
            const ColumnT &column;
        };


        template<class NameType>
        class column_t : public column_expression<column_t<NameType>> {
        public:
            constexpr column_t(const detail::constexpr_string_base<NameType> &name)
                    : COLLATE{*this}, name{name} {}

            constexpr auto to_str() const { return name; }
            constexpr auto get_name() const { return name; }

            template <class RightColumnT>
            constexpr auto operator,(const column_base<RightColumnT> &right_column) const {
                return column_comma_list<column_t<NameType>, RightColumnT>{*this, right_column};
            };

            template <class ExpressionT>
            constexpr auto operator=(const expression<ExpressionT> &expression) const {
                return column_equals_expression<column_t<NameType>, ExpressionT>{*this, expression};
            }

            collate_expression_member<column_t<NameType>> COLLATE;

        private:
            NameType name;
        };

        template <class T>
        struct column_comma_list_base {
            constexpr auto to_str() const { return static_cast<const T *>(this)->to_str(); }
            constexpr const auto &get_columns() const { return static_cast<const T *>(this)->get_columns(); }
        };

        template <class ... ColumnT>
        class column_comma_list : public column_comma_list_base<column_comma_list<ColumnT...>> {
        public:
            constexpr column_comma_list(const column_base<ColumnT> & ... columns)
                : columns{columns...} {}

            template <class ... ColumnTs, class RightColumnT, std::size_t ... Index>
            constexpr column_comma_list(const column_comma_list_base<ColumnTs...> &columns, const column_base<RightColumnT> &column, std::index_sequence<Index...>)
                : columns{std::get<Index>(columns.get_columns())..., column} {}

            constexpr auto to_str() const {
                return make_columns_str(std::make_index_sequence<sizeof...(ColumnT)>());
            }

            template <class ExpressionT>
            constexpr auto operator=(const expression<ExpressionT> &expression) {
                return column_comma_list_equals_expression<column_comma_list<ColumnT...>, ExpressionT>{*this, expression};
            }

            constexpr const auto &get_columns() const { return columns; }

        private:
            template <std::size_t ... Index>
            constexpr auto make_columns_str(std::index_sequence<Index...>) const {
                return join_constexpr_strings(sql_strings::OPEN_PARENTHESIS,
                                              sql_strings::COMMA.join(std::get<Index>(columns).get_name()...),
                                              sql_strings::CLOSE_PARENTHESIS
                );
            }

        private:
            std::tuple<const column_base<ColumnT> & ...> columns;
        };

        template <class ColumnT, class ExpressionT>
        class column_equals_expression : public column_equals_statement_base<column_equals_expression<ColumnT, ExpressionT>> {
        public:
            constexpr column_equals_expression(const column_base<ColumnT> &column, const expression<ExpressionT> &expression)
                : column{static_cast<const ColumnT &>(column)}, expression{static_cast<const ExpressionT &>(expression)} {}

            constexpr auto to_str() const {
                return sql_strings::EQUALS.join(
                    column.get_name(),
                    expression.to_str()
                );
            }

        private:
            const ColumnT &column;
            const ExpressionT &expression;
        };

        template <class ColumnListT, class ExpressionT>
        class column_comma_list_equals_expression : public column_equals_statement_base<column_comma_list_equals_expression<ColumnListT, ExpressionT>> {
        public:
            constexpr column_comma_list_equals_expression(const column_comma_list_base<ColumnListT> &column_list, const expression<ExpressionT> &expression)
                : column_list{static_cast<const ColumnListT &>(column_list)}, expression{static_cast<const ExpressionT &>(expression)} {}

            constexpr auto to_str() const {
                return sql_strings::EQUALS.join(
                    column_list.to_str(),
                    expression.to_str()
                );
            }

        private:
            const ColumnListT &column_list;
            const ExpressionT &expression;
        };

    }
}
