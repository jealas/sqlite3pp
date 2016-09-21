#pragma once

#include "sqlite3pp/detail/constexpr_string.hxx"


namespace sqlite3pp {
    namespace sql {

        class column_view {
        public:
            template<class ColumnT>
            constexpr column_view(const column_base<ColumnT> &column)
                    : name{column.get_name()}, column_type{column.get_type()} { }

            constexpr bool operator==(const column_view &other_column_view) const {
                return column_type == other_column_view.column_type && name == other_column_view.name;
            }

        private:
            const detail::constexpr_string_view name;
            const sql::column_type column_type;
        };

    }
}