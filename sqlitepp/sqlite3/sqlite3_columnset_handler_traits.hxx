#pragma once

#include <tuple>


namespace sqlitepp {
    namespace sqlite3 {

        template <class T>
        struct sqlite3_columnset_handler_traits : public sqlite3_columnset_handler_traits<decltype(&T::operator())> {};

        template <class ReturnT, class ... Args>
        struct sqlite3_columnset_handler_traits<ReturnT(Args...)> {
            static constexpr std::size_t arity = sizeof...(Args);

            using return_t = ReturnT;

            template <std::size_t I>
            using arg_t = std::tuple_element_t<I, std::tuple<Args...>>;
        };

        template <class ClassT, class ReturnT, class... Args>
        struct sqlite3_columnset_handler_traits<ReturnT(ClassT::*)(Args...) const> {
            static constexpr std::size_t arity = sizeof...(Args);

            using return_t = ReturnT;

            template <std::size_t I>
            using arg_t = std::tuple_element_t<I, std::tuple<Args...>>;
        };

    }
}