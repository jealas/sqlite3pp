#pragma once

#include "sqlitepp/detail/constexpr_string.hxx"

namespace sqlitepp {
    namespace sql {

        template<class CharT>
        class column_view {
        public:
            template<class ColumnT>
            constexpr column_view(const column_base<ColumnT> &column)
                    : name{column.get_name()}, column_type{column.get_type()} { }

            constexpr bool operator==(const column_view<CharT> &other_column_view) const {
                return column_type == other_column_view.column_type && name == other_column_view.name;
            }

        private:
            const detail::constexpr_string_view<CharT> name;
            const sql::column_type column_type;
        };

    }
}