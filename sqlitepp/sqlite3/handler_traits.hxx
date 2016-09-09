#pragma once

#include <tuple>


namespace sqlitepp {
    namespace sqlite3 {

        template <class T>
        struct handler_traits;

        template <class T>
        struct handler_traits : public handler_traits<decltype(&T::operator())> {};

        template <class ClassT, class ReturnT, class... Args>
        struct handler_traits<ReturnT(ClassT::*)(Args...) const> {
            static constexpr std::size_t arity = sizeof...(Args);

            using return_t = ReturnT;

            template <std::size_t I>
            using arg_t = std::tuple_element_t<I, std::tuple<Args...>>;
        };

        template <class ClassT, class ReturnT, class... Args>
        struct handler_traits<ReturnT(ClassT::*)(Args...)> {
            static constexpr std::size_t arity = sizeof...(Args);

            using return_t = ReturnT;

            template <std::size_t I>
            using arg_t = std::tuple_element_t<I, std::tuple<Args...>>;
        };

    }
}