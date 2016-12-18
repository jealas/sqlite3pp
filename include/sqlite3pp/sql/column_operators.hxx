#pragma once

#include <type_traits>
#include <tuple>

#include "sqlite3pp/sql/column.hxx"


namespace {

    template <class ... ColumnT, class RightColumnT, std::size_t ... ColumnIndex>
    constexpr auto make_comma_list_helper(const std::tuple<const ColumnT & ...> &columns, const column_base<RightColumnT> &column, std::index_sequence<ColumnIndex...>) {
        return column_comma_list<ColumnT..., RightColumnT>{std::get<ColumnIndex>(columns)..., column};
    }

}


namespace sqlite3pp {
    namespace sql {
        namespace operators {

            template <class ColumnListT, class RightColumnT>
            constexpr auto operator,(const column_comma_list_base<ColumnListT> &column_list, const column_base<RightColumnT> &column) {
                return make_comma_list_helper(column_list.get_columns(), column, std::make_index_sequence<std::tuple_size<std::decay_t<decltype(column_list.get_columns())>>::value>());
            };

        }
    }
}