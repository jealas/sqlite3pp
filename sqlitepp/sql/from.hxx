#pragma once

namespace sqlitepp {
    namespace sql {

        template <class Table>
        class from_table_t {
        public:
            explicit constexpr from_table_t(const Table & table) : table{table} {}

            constexpr const Table & get_table() const { return table; }

        private:
            const Table table;
        };

        struct from_t {
            template <class Table>
            constexpr auto operator[](const Table & table) const { return from_table_t<Table>{table}; }
        };

        constexpr from_t from;
    }
}

