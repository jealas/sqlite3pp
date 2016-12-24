#pragma once

#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/column_definition_statement.hxx"


namespace sqlite3pp {
    namespace sql {
        // Base classes
        template <class T>
        struct create_table_base {
            constexpr auto serialize() const { return static_cast<const T *>(this)->serialize(); }
        };

        template <class T>
        struct create_table_syntax_base {
            constexpr auto to_str() const { return static_cast<const T *>(this)->to_str(); }
        };

        // Forward declarations.
        template <class CreateTableSyntaxT>
        class create_table_table_syntax;

        // Statements
        template <class CreateTableSyntaxT, class TableT>
        class create_table_statement : public create_table_syntax_base<create_table_statement<CreateTableSyntaxT, TableT>> {
        public:
            constexpr create_table_statement(const create_table_syntax_base<CreateTableSyntaxT> &create, const table_base<TableT> &table)
                : create{static_cast<const CreateTableSyntaxT &>(create)},
                  table{static_cast<const TableT &>(table)} {}

            template <class ... ColumnDefinitionT>
            constexpr auto operator()(const column_definition_base<ColumnDefinitionT> & ... column_def) const {

            }

            constexpr auto to_str() const { return sql_strings::SPACE.join(create.to_str(), table.get_name()); }

        private:
            const CreateTableSyntaxT &create;
            const TableT &table;
        };

        // Member variables
        template <class CreateTableSyntaxT>
        class create_temporary_table_syntax : public create_table_syntax_base<create_temporary_table_syntax<CreateTableSyntaxT>> {
        public:
            constexpr create_temporary_table_syntax(const create_table_syntax_base<CreateTableSyntaxT> &create)
                : TABLE{*this},
                  create{static_cast<const CreateTableSyntaxT &>(create)} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(create.to_str(), sql_strings::TEMPORARY); }

            create_table_table_syntax<create_temporary_table_syntax<CreateTableSyntaxT>> TABLE;

        private:
            const CreateTableSyntaxT &create;
        };

        template <class CreateTableSyntaxT>
        class create_temp_table_syntax : public create_table_syntax_base<create_temp_table_syntax<CreateTableSyntaxT>> {
        public:
            constexpr create_temp_table_syntax(const create_table_syntax_base<CreateTableSyntaxT> &create)
                    : TABLE{*this},
                      create{static_cast<const CreateTableSyntaxT &>(create)} {}

            constexpr auto to_str() const {
                    return sql_strings::SPACE.join(create.to_str(), sql_strings::TEMP);
            }

            create_table_table_syntax<create_temp_table_syntax<CreateTableSyntaxT>> TABLE;

        private:
            const CreateTableSyntaxT &create;
        };

        template <class CreateTableSyntaxT>
        class create_table_table_syntax : public create_table_syntax_base<create_table_table_syntax<CreateTableSyntaxT>> {
        public:
            constexpr create_table_table_syntax(const create_table_syntax_base<CreateTableSyntaxT> &create)
                : create{static_cast<const CreateTableSyntaxT &>(create)} {}

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return create_table_statement<create_table_table_syntax<CreateTableSyntaxT>, TableT>{*this, table};
            }

            constexpr auto to_str() const { return sql_strings::SPACE.join(create.to_str(), sql_strings::TABLE); }

        private:
            const CreateTableSyntaxT &create;
        };


        // IF NOT EXISTS

    }
}