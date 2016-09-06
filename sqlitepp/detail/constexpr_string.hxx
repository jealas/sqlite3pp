#pragma once

#include <initializer_list>

#include "sqlitepp/detail/constexpr_string_view.hxx"


namespace {
    constexpr std::size_t sum(const std::initializer_list<std::size_t> sizes) {
        std::size_t sum = 0u;

        for (auto size : sizes) {
            sum += size;
        }

        return sum;
    }

}

namespace sqlitepp {
    namespace detail {

        template <class T>
        struct constexpr_string_base {
            constexpr auto begin() const { return static_cast<const T *>(this)->begin(); }
            constexpr auto end() const { return static_cast<const T *>(this)->end(); }
            constexpr auto &operator[](std::size_t i) { return *static_cast<T *>(this)[i]; }
            constexpr const auto &operator[](std::size_t i) const { return *static_cast<const T *>(this)[i]; }
            constexpr std::size_t length() const { return static_cast<const T *>(this)->length(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

        template<std::size_t Length>
        class constexpr_string : public constexpr_string_base<constexpr_string<Length>> {
        public:
            constexpr constexpr_string() : str_data{} { }

            constexpr constexpr_string(const char (&str)[Length + 1u]) : str_data{} {
                for (auto i = 0u; i < Length; ++i) {
                    str_data[i] = str[i];
                }
            }

            constexpr constexpr_string(const constexpr_string<Length> &str) : str_data{} {
                for (auto i = 0u; i < Length; ++i) {
                    str_data[i] = str[i];
                }
            }

            constexpr const char *begin() const { return str_data; }
            constexpr const char *end() const { return str_data + Length; }

            constexpr char &operator[](std::size_t i) { return str_data[i]; }
            constexpr const char &operator[](std::size_t i) const { return str_data[i]; }

            constexpr std::size_t length() const { return Length; }

            template<std::size_t ... Sizes>
            constexpr auto join(const constexpr_string<Sizes> &... strings) const {

                static_assert(sizeof...(Sizes) > 0u, "You must join at least one string.");

                constexpr std::size_t NEW_STRING_LENGTH = sum(Sizes...) + (Length * (sizeof...(Sizes) - 1u));
                constexpr_string<NEW_STRING_LENGTH> new_string{};

                std::size_t index = 0u;

                auto all_strings = std::initializer_list<constexpr_string_view>{strings...};

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

                return new_string;
            };

            constexpr auto c_str() const {
                constexpr_string<Length + 1u> c_string;

                for (auto i = 0u; i < Length; ++i) {
                    c_string[i] = str_data[i];
                }

                c_string[Length] = '\0';

                return c_string;
            }

            constexpr operator constexpr_string_view() {
                return {&str_data[0], Length};
            }

        private:
            char str_data[Length];
        };

        template<std::size_t Length>
        constexpr constexpr_string<Length - 1u> make_constexpr_string(const char (&str)[Length]) {
            constexpr_string<Length - 1u> new_string{};

            for (auto i = 0u; i < Length - 1u; ++i) {
                new_string[i] = str[i];
            }

            return new_string;
        }

    }
}
