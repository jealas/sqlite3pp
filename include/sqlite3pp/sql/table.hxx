#pragma once

#include <tuple>
#include <utility>
#include <initializer_list>

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"


namespace sqlite3pp {
    namespace sql {

        template<class T>
        struct table_base {
            constexpr auto get_name() const { return static_cast<const T *>(this)->get_name(); }
        };

        template<class TableNameT, class ... Columns>
        class table_t : public table_base<table_t<TableNameT, Columns...>>, public Columns::template member_t<Columns>... {
        public:
            constexpr table_t(const detail::constexpr_string_base<TableNameT> &name, const column_base<Columns> &... columns)
                    : Columns::template member_t<Columns>{columns, }..., name{name}, columns{columns...} { }

            constexpr auto get_name() const { return name; }

        private:
            TableNameT name;
            std::tuple<Columns...> columns;
        };

    }
}
