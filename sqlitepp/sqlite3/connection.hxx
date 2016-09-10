#pragma once

#include <sqlite3.h>

#include "sqlitepp/sqlite3/expected.hxx"
#include "sqlitepp/sqlite3/error.hxx"


namespace sqlitepp {
    namespace sqlite3 {

        using open_option = int;

        static constexpr open_option OPEN_NOMUTEX = SQLITE_OPEN_NOMUTEX;
        static constexpr open_option OPEN_FULLMUTEX = SQLITE_OPEN_FULLMUTEX;
        static constexpr open_option OPEN_SHAREDCACHE = SQLITE_OPEN_SHAREDCACHE;
        static constexpr open_option OPEN_PRIVATECACHE = SQLITE_OPEN_PRIVATECACHE;
        static constexpr open_option OPEN_URI = SQLITE_OPEN_URI;

        static constexpr open_option OPEN_READONLY = SQLITE_OPEN_READONLY;
        static constexpr open_option OPEN_READWRITE = SQLITE_OPEN_READWRITE;
        static constexpr open_option OPEN_CREATE = SQLITE_OPEN_CREATE;

        class connection;
        auto make_connection(const char * filename, open_option options) -> expected<connection>;
        auto make_connection(const char * filename) -> expected<connection>;

        class connection {
        public:
            ~connection();

            auto close() -> error;

            operator ::sqlite3 *() { return connection_ptr; }

        private:
            connection(::sqlite3 * connection) : connection_ptr{connection} {}

            friend auto make_connection(const char *, open_option) -> expected<connection>;
            friend auto make_connection(const char*) -> expected<connection>;

        private:
            ::sqlite3 *connection_ptr;
        };

    }
}