#pragma once

namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct serializable {
            constexpr auto to_str() const { return static_cast<const T *>(this)->to_str(); }
            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }
        };

    }
}