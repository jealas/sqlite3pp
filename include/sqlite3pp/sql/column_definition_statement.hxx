#pragma once

namespace sqlite3pp {
    namespace sql {

        template <class T>
        struct column_definition_base {
            constexpr auto serialize() const { return static_cast<const T *>(this)->serialize(); }
        };



    }
}
