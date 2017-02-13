#pragma once


#include "sqlite3pp/sql/table.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"

namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct update_base {
            constexpr auto serialize() const { return static_cast<const T *>(this)->serialize(); }
        };

        template <class UpdateSyntaxT>
        struct update_syntax {
            constexpr auto to_str() const { return static_cast<const UpdateSyntaxT *>(this)->to_str(); }
        };

        template <class UpdateSyntaxT, class TableT>
        class update_with_table : public update_syntax<update_with_table<UpdateSyntaxT, TableT>> {
        public:
            constexpr update_with_table(const update_syntax<UpdateSyntaxT> &update_syntax, const table_base<TableT> &table)
                : update_syntax{update_syntax}, table{table} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), table.get_name()); }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
            const table_base<TableT> &table;
        };

        template <class UpdateSyntaxT>
        class update_rollback_syntax : public update_syntax<update_rollback_syntax<UpdateSyntaxT>> {
        public:
            constexpr update_rollback_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::ROLLBACK); }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return update_with_table<update_rollback_syntax<UpdateSyntaxT>, TableT>{*this, table};
            }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_abort_syntax : public update_syntax<update_abort_syntax<UpdateSyntaxT>> {
        public:
            constexpr update_abort_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::ABORT); }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return update_with_table<update_abort_syntax<UpdateSyntaxT>, TableT>{*this, table};
            }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_replace_syntax : public update_syntax<update_replace_syntax<UpdateSyntaxT>> {
        public:
            constexpr update_replace_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::REPLACE); }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return update_with_table<update_replace_syntax<UpdateSyntaxT>, TableT>{*this, table};
            }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_fail_syntax : public update_syntax<update_fail_syntax<UpdateSyntaxT>> {
        public:
            constexpr update_fail_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::FAIL); }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return update_with_table<update_fail_syntax<UpdateSyntaxT>, TableT>{*this, table};
            }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_ignore_syntax : public update_syntax<update_ignore_syntax<UpdateSyntaxT>> {
        public:
            constexpr update_ignore_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::IGNORE); }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return update_with_table<update_ignore_syntax<UpdateSyntaxT>, TableT>{*this, table};
            }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_or_member : public update_syntax<update_or_member<UpdateSyntaxT>> {
        public:
            constexpr update_or_member(const update_syntax<UpdateSyntaxT> &update_syntax)
                : update_syntax{update_syntax},
                  ROLLBACK{*this},
                  ABORT{*this},
                  REPLACE{*this},
                  FAIL{*this},
                  IGNORE{*this} {}

        public:
            update_rollback_syntax<update_or_member<UpdateSyntaxT>> ROLLBACK;
            update_abort_syntax<update_or_member<UpdateSyntaxT>> ABORT;
            update_replace_syntax<update_or_member<UpdateSyntaxT>> REPLACE;
            update_fail_syntax<update_or_member<UpdateSyntaxT>> FAIL;
            update_ignore_syntax<update_or_member<UpdateSyntaxT>> IGNORE;

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::OR); }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        class update_member : public update_syntax<update_member> {
        public:
            constexpr update_member() : OR{*this} {}

            constexpr auto to_str() const { return sql_strings::UPDATE; }

            template <class TableT>
            constexpr auto operator()(const table_base<TableT> &table) const {
                return update_with_table<update_member, TableT>{*this, table};
            }

        public:
            update_or_member<update_member> OR;
        };

    }
}