#pragma once

#include <tuple>
#include <utility>
#include <initializer_list>

#include "sqlitepp/sql/column.hxx"
#include "sqlitepp/sql/sql_strings.hxx"
#include "sqlitepp/sql/column_set.hxx"


namespace sqlitepp {
    namespace sql {

        template<class T>
        struct table_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }

            constexpr auto get_columns() const { return static_cast<const T *>(this)->get_columns(); }

            constexpr operator T() const { return *static_cast<const T *>(this); }
        };

        template<class CharT, class TableNameT, class AliasNameT, class ... ColumnTypes>
        class table_with_alias_t
                : public table_base<table_with_alias_t<CharT, TableNameT, AliasNameT, ColumnTypes...>> {
        public:
            constexpr table_with_alias_t(const detail::constexpr_string_base<TableNameT> &table_name,
                                         const detail::constexpr_string_base<AliasNameT> &alias_name,
                                         const column_set<ColumnTypes...> &columns)
                    : name{table_name}, alias_name{alias_name}, columns{columns} { }

        private:
            const TableNameT name;
            const AliasNameT alias_name;
            const column_set<ColumnTypes...> columns;
        };

        template<class CharT, class TableNameT, class ... Columns>
        class table_t : public table_base<table_t<CharT, TableNameT, Columns...>> {
        public:
            constexpr table_t(const detail::constexpr_string_base<TableNameT> &name,
                              const column_base<Columns> &... columns)
                    : name{name}, columns{columns...} { }

            constexpr auto get_name() const { return name; }

            constexpr auto get_columns() const { return columns; }

            template<std::size_t AliasNameLength>
            constexpr auto as(const CharT (&alias_name)[AliasNameLength]) const {
                auto alias_name_str = sqlitepp::detail::make_constexpr_string(alias_name);

                return table_with_alias_t<CharT, TableNameT, decltype(alias_name_str), Columns...>{name, alias_name_str,
                                                                                                   columns};
            }

        private:
            const TableNameT name;
            const column_set<Columns...> columns;
        };

        template<class CharT, class SchemaNameType, class TableNameType, class AliasNameType, class ... Columns>
        class table_with_schema_and_alias_t
                : public table_base<table_with_schema_and_alias_t<CharT, SchemaNameType, TableNameType, AliasNameType, Columns...>> {
        public:
            constexpr table_with_schema_and_alias_t(const detail::constexpr_string_base<SchemaNameType> &schema_name,
                                                    const detail::constexpr_string_base<TableNameType> &table_name,
                                                    const detail::constexpr_string_base<AliasNameType> &alias_name,
                                                    const column_set<Columns...> &columns)
                    : schema_name{schema_name}, name{table_name}, alias_name{alias_name}, columns{columns} { }

        private:
            const SchemaNameType schema_name;
            const TableNameType name;
            const AliasNameType alias_name;
            const column_set<Columns...> columns;
        };

        template<class CharT, class SchemaNameType, class TableNameType, class ... Columns>
        class table_with_schema_t
                : public table_base<table_with_schema_t<CharT, SchemaNameType, TableNameType, Columns...>> {
        public:
            constexpr table_with_schema_t(const detail::constexpr_string_base<SchemaNameType> &schema_name,
                                          const detail::constexpr_string_base<TableNameType> &table_name,
                                          const column_base<Columns> &... columns)
                    : schema_name{schema_name}, name{table_name}, columns{columns...} { }

            constexpr auto get_name() const { return name; }

            constexpr auto get_columns() const { return columns; }

            template<std::size_t AliasNameLength>
            constexpr auto as(const CharT (&alias_name)[AliasNameLength]) const {
                auto alias_name_str = sqlitepp::detail::make_constexpr_string(alias_name);

                return table_with_schema_and_alias_t<CharT, SchemaNameType, TableNameType, decltype(alias_name_str), Columns...>{
                        schema_name, name, alias_name_str, columns};
            }

        private:
            const SchemaNameType schema_name;
            const TableNameType name;
            const column_set<Columns...> columns;
        };


        template<std::size_t TableNameLength, class ... ColumnTypes>
        constexpr auto table(const char (&name)[TableNameLength], const column_base<ColumnTypes> &... columns) {
            auto name_str = detail::make_constexpr_string(name);

            return table_t<char, decltype(name_str), ColumnTypes...>{name_str, columns...};
        }

        template<std::size_t TableLengthName, class ... ColumnTypes>
        constexpr auto table(const char16_t (&name)[TableLengthName], const column_base<ColumnTypes> &... columns) {
            auto name_str = detail::make_constexpr_string(name);

            return table_t<char16_t, decltype(name_str), ColumnTypes...>{name_str, columns...};
        };

        template<std::size_t SchemaNameLength, std::size_t TableNameLength, class ... ColumnTypes>
        constexpr auto table(const char (&schema_name)[SchemaNameLength], const char (&table_name)[TableNameLength],
                             const column_base<ColumnTypes> &... columns) {
            auto schema_name_str = detail::make_constexpr_string(schema_name);
            auto table_name_str = detail::make_constexpr_string(table_name);

            return table_with_schema_t<char, decltype(schema_name_str), decltype(table_name_str), ColumnTypes...>{
                    schema_name_str, table_name_str, columns...};
        };

        template<std::size_t SchemaNameLength, std::size_t TableNameLength, class ... ColumnTypes>
        constexpr auto table(const char16_t (&schema_name)[SchemaNameLength],
                             const char16_t (&table_name)[TableNameLength],
                             const column_base<ColumnTypes> &... columns) {

            auto schema_name_str = detail::make_constexpr_string(schema_name);
            auto table_name_str = detail::make_constexpr_string(table_name);

            return table_with_schema_t<char16_t, decltype(schema_name_str), decltype(table_name_str), ColumnTypes...>{
                    schema_name_str, table_name_str, columns...};
        };

    }
}
