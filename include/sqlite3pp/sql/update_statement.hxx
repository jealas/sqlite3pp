#pragma once


#include "sql_strings.hxx"

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

        template <class UpdateSyntaxT>
        class update_rollback_syntax {
        public:
            constexpr update_rollback_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::ROLLBACK); }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_abort_syntax {
        public:
            constexpr update_abort_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::ABORT); }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_replace_syntax {
        public:
            constexpr update_replace_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::REPLACE); }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_fail_syntax {
        public:
            constexpr update_fail_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::FAIL); }

        private:
            const update_syntax<UpdateSyntaxT> &update_syntax;
        };

        template <class UpdateSyntaxT>
        class update_ignore_syntax {
        public:
            constexpr update_ignore_syntax(const update_syntax<UpdateSyntaxT> &update_syntax)
                    : update_syntax{update_syntax} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(update_syntax.to_str(), sql_strings::IGNORE); }

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

            update_or_member<update_member> OR;

        };

    }
}