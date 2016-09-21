#pragma once

#include <utility>
#include <sqlite3.h>

#include "sqlite3pp/sqlite3/error.hxx"
#include "sqlite3pp/sqlite3/connection.hxx"
#include "sqlite3pp/sqlite3/expected.hxx"
#include "sqlite3pp/sql/str.hxx"


namespace sqlite3pp {
    namespace sqlite3 {

        class prepared_statement;
        auto make_prepared_statement(connection &conn, const sql::str &sql_str) -> expected<prepared_statement>;
        auto make_prepared_statement_v1(connection &conn, const sql::str &sql_str) -> expected<prepared_statement>;

        class prepared_statement {
        public:
            ~prepared_statement();

            prepared_statement(prepared_statement &&other) : prepared_statement_prt{nullptr} {
                std::swap(prepared_statement_prt, other.prepared_statement_prt);
            }

            error finalize();

            explicit operator bool() const { return prepared_statement_prt != nullptr; }
            operator sqlite3_stmt *() { return prepared_statement_prt; }

        private:
            prepared_statement() : prepared_statement_prt{nullptr} {}

            prepared_statement(sqlite3_stmt *prepared_statement_ptr)
                : prepared_statement_prt{prepared_statement_ptr} {}

            friend auto make_prepared_statement(connection & conn, const sql::str &sql_str) -> expected<prepared_statement>;
            friend auto make_prepared_statement_v1(connection & conn, const sql::str &sql_str) -> expected<prepared_statement>;

        private:
            sqlite3_stmt *prepared_statement_prt;
        };

        prepared_statement::~prepared_statement() {
            finalize();
        }

        error prepared_statement::finalize() {
            auto err = static_cast<error>(sqlite3_finalize(prepared_statement_prt));
            prepared_statement_prt = nullptr;

            return err;
        }

    }
}