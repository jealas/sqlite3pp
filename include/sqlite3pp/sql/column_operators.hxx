#pragma once

#include <type_traits>

#include "sqlite3pp/sql/column.hxx"


namespace sqlite3pp {
    namespace sql {
        namespace operators {

//            template <class LeftColumn, class RightColumn>
//            constexpr auto operator,(const column_base<LeftColumn> &left_column, const column_base<RightColumn> &right_column) {
//                return column_comma_list<LeftColumn, RightColumn>{left_column, right_column};
//            };

            template <class ... ColumnT, class RightColumnT>
            constexpr column_comma_list<ColumnT..., RightColumnT> operator,(const column_comma_list_base<ColumnT...> &column_list, const column_base<RightColumnT> &column) {
                return {column_list, column, std::make_index_sequence<sizeof...(ColumnT)>()};
            };

        }
    }
}