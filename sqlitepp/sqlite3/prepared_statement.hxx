#pragma once

#include <utility>
#include <sqlite3.h>

#include "sqlitepp/sqlite3/error.hxx"


namespace sqlitepp {
    namespace sqlite3 {

        class prepared_statement;
        prepared_statement make_prepared_statement();

        class prepared_statement {
        public:
            ~prepared_statement();

            prepared_statement(prepared_statement &&other) : prepared_statement_prt{nullptr} {
                std::swap(prepared_statement_prt, other.prepared_statement_prt);
            }

            error finalize();

            explicit operator bool() const { return prepared_statement_prt != nullptr; }
            explicit operator const sqlite3_stmt *() const { return prepared_statement_prt; }

        private:
            prepared_statement() : prepared_statement_prt{nullptr} {}

            prepared_statement(sqlite3_stmt *prepared_statement_ptr)
                : prepared_statement_prt{prepared_statement_ptr} {}

            friend prepared_statement make_prepared_statement();

        private:
            sqlite3_stmt *prepared_statement_prt;
        };

        prepared_statement::~prepared_statement() {
            if (prepared_statement_prt != nullptr) {
                finalize();
            }
        }

        error prepared_statement::finalize() {
            auto err = static_cast<error>(sqlite3_finalize(prepared_statement_prt));
            prepared_statement_prt = nullptr;

            return err;
        }

        prepared_statement make_prepared_statement() {
        }

    }
}