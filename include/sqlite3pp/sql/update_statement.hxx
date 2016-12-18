#pragma once


#include "sql_strings.hxx"

namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct update_base {
            constexpr auto serialize() const { return static_cast<const T *>(this)->serialize(); }
        };

        template <class UpdateSyntaxT>
        struct update_syntax {
            constexpr auto to_str() const { return static_cast<const UpdateSyntaxT *>(this)->to_str(); }
        };


        struct update_member : public update_syntax<update_member> {
            constexpr auto to_str() const { return sql_strings::UPDATE; }
        };


    }
}