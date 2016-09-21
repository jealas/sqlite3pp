#pragma once

#include <initializer_list>
#include <utility>

#include "sqlite3pp/detail/constexpr_string_view.hxx"


namespace {

    template <std::size_t ... Sizes>
    constexpr std::size_t sum() {
        std::size_t sum = 0u;

        for (auto size : {Sizes...}) {
            sum += size;
        }

        return sum;
    }

}

namespace sqlite3pp {
    namespace detail {

        template <class T>
        struct constexpr_string_base {
            constexpr auto begin() const { return static_cast<const T *>(this)->begin(); }
            constexpr auto end() const { return static_cast<const T *>(this)->end(); }
            constexpr const auto &operator[](std::size_t i) const { return *static_cast<const T *>(this)[i]; }
            constexpr std::size_t length() const { return static_cast<const T *>(this)->length(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

        template<std::size_t Length>
        class constexpr_string : public constexpr_string_base<constexpr_string<Length>> {

            template <std::size_t ... Indexes>
            constexpr constexpr_string(const char(&str)[Length + 1u], std::index_sequence<Indexes...>)
                : str_data{str[Indexes]...} {}

            template <std::size_t ... Indexes>
            constexpr constexpr_string(const char(&str)[Length], std::index_sequence<Indexes...>)
                : str_data{str[Indexes]...} {}

            constexpr constexpr_string(const char(&str)[Length])
                : constexpr_string{str, std::make_index_sequence<Length>()} {}

            // For c_str function.
            friend class constexpr_string<Length - 1u>;

        public:
            constexpr constexpr_string(const char(&str)[Length + 1u])
                : constexpr_string{str, std::make_index_sequence<Length>()} {

                if (str[Length] != '\0') {
                    throw std::runtime_error("Cannot initialize constexpr string with an array.");
                }

            }

            constexpr constexpr_string(const constexpr_string<Length> &str)
                : constexpr_string{str.str_data, std::make_index_sequence<Length>()} {}

            constexpr const char *begin() const { return str_data; }
            constexpr const char *end() const { return str_data + Length; }

            constexpr const char &operator[](std::size_t i) const { return str_data[i]; }

            template <std::size_t OtherStringLength>
            constexpr auto operator+(const constexpr_string<OtherStringLength> & other_str) {
                constexpr_string<OtherStringLength + Length> new_str;

                for (auto i = 0u; i < Length; ++i) {
                    new_str[i] = str_data[i];
                }

                for (auto i = Length; i < Length + OtherStringLength; ++i) {
                    new_str[i] = str_data[i];
                }

                return new_str;
            }

            constexpr std::size_t length() const { return Length; }

            template<std::size_t ... Sizes>
            constexpr auto join(const constexpr_string<Sizes> &... strings) const {

                static_assert(sizeof...(Sizes) > 0u, "You must join at least one string.");

                constexpr std::size_t NEW_STRING_LENGTH = sum<Sizes...>() + (Length * (sizeof...(Sizes) - 1u));
                char new_string[NEW_STRING_LENGTH + 1u] = {'\0'};

                std::size_t index = 0u;

                auto all_strings = {constexpr_string_view{strings}...};

                for (auto current_string = all_strings.begin(); current_string != all_strings.end(); ++current_string) {
                    for (auto c : *current_string) {
                        new_string[index++] = c;
                    }

                    if (current_string + 1u == all_strings.end()) {
                        break;
                    }

                    for (auto c : *this) {
                        new_string[index++] = c;
                    }
                }

                return constexpr_string<NEW_STRING_LENGTH>{new_string};
            };

            constexpr auto c_str() const {
                char c_string[Length + 1u] = {'\0'};

                for (auto i = 0u; i < Length; ++i) {
                    c_string[i] = str_data[i];
                }

                return constexpr_string<Length + 1u>{c_string};
            }

            constexpr operator constexpr_string_view() const {
                return {&str_data[0], Length};
            }

        private:
            char str_data[Length];
        };

        template<std::size_t Length>
        constexpr auto make_constexpr_string(const char (&str)[Length]) {
            return constexpr_string<Length - 1u>{str};
        }

    }
}
