#pragma once

#include "sqlitepp/sql/expression_type.hxx"


namespace sqlitepp {
    namespace sql {

        template <class T>
        struct expression_base {
            auto get_str() const { return static_cast<const T*>(this)->get_str(); }
            expression_type get_type() const { return static_cast<const T*>(this)->get_type(); }
            constexpr operator T() const { return *static_cast<const T*>(this); }
        };

    }
}