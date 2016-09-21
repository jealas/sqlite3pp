#pragma once

#include <cstdint>
#include <utility>

#include "sqlitepp/sqlite3/error.hxx"


namespace sqlitepp {
    namespace sqlite3 {

        template <class T>
        class expected {

            enum class expected_state : std::uint8_t {
                VALUE,
                ERROR
            };

        public:
            ~expected();
            expected(error e) : err{e}, state{expected_state::ERROR} {}
            expected(T value) : value{std::move(value)}, state{expected_state::VALUE} {};

            expected(expected<T> &&other) : value{std::move(other.value)}, state{other.state} {};

            expected(expected<T> &other) = delete;
            expected<T> &operator=(const expected<T> &other) = delete;
            expected<T> &operator=(expected<T> &&other) = delete;

            bool has_error() const { return state == expected_state::ERROR; }
            bool has_value() const { return state == expected_state::VALUE; }

            T * get_value() { return state == expected_state::ERROR ? nullptr : &value; }
            const T * get_value() const { return state == expected_state::ERROR ? nullptr : &value; }

            const error * get_error() const { return state == expected_state::ERROR ? err : nullptr; }

            explicit operator bool() const { return state != expected_state::ERROR; }

        private:
            union {
                T value;
                error err;
            };

            expected_state state;
        };

        template <class T>
        expected<T>::~expected() {
            if (state == expected_state::VALUE) {
                value.~T();
            }
        }

    }
}