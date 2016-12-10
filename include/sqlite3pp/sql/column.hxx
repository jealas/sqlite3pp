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

            collate_expression_member<column_t<NameType>> COLLATE;

        private:
            NameType name;
        };

    }
}
