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

        template<class TableT, class TableNameT>
        class table_t : public TableT, public table_base<table_t<TableT, TableNameT>> {
        public:
            constexpr table_t(const detail::constexpr_string_base<TableNameT> &name)
                : __name{name} { }

            constexpr auto get_name() const { return __name; }

        private:
            TableNameT __name;
        };

    }
}
