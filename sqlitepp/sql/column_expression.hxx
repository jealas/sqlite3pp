#pragma once

#include "sqlitepp/sql/column.hxx"


namespace sqlitepp {
    namespace sql {

    template <class ColumnT>
    class unary_column_expression {
    public:

    private:
        const ColumnT column;
    };

    template <class ColumnT>
    class binary_column_expression {
    public:

    private:
    };

    }
}