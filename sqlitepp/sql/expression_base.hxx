#pragma once

#include "sqlitepp/sql/expression_type.hxx"


namespace sqlitepp {
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