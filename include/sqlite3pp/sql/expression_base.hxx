#pragma once

#include "expression_type.hxx"


namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct expression_base {
            constexpr auto get_str() const { return static_cast<const T*>(this)->get_str(); }
            constexpr expression_type get_type() const { return static_cast<const T*>(this)->get_type(); }

            constexpr operator const T&() const { return *static_cast<const T *>(this); }
            constexpr operator T&() { return *static_cast<T *>(this); }
        };

    }
}