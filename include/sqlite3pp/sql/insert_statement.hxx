#pragma once

#include "sqlite3pp/sql/sql_strings.hxx"


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

        template <class InsertSyntaxT>
        class insert_into_member {
        public:
            constexpr insert_into_member(const insert_syntax_base<InsertSyntaxT> &insert)
                : insert{static_cast<const InsertSyntaxT &>(insert)} {}

            constexpr auto to_str() const {
                return sql_strings::SPACE.join(
                    insert.to_str(),
                    sql_strings::INTO
                );
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