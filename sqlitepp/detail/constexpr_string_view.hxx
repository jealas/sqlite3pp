#pragma once

namespace sqlitepp {
    namespace detail {

        class constexpr_string_view {
        public:
            constexpr constexpr_string_view(const char *data, std::size_t length)
                    : data{data}, length{length} { }

            constexpr bool operator==(const constexpr_string_view &other) const {
                if (length != other.length) {
                    return false;
                }

                for (auto i = 0u; i < length; ++i) {
                    if (data[i] != other.data[i]) {
                        return false;
                    }
                }

                return true;
            }

            constexpr const char *begin() const { return data; }
            constexpr const char *end() const { return data + length; }

        private:
            const char *data;
            const std::size_t length;
        };

    }
}