#pragma once

#include "sqlitepp/sqlite3/expected.hxx"


namespace sqlitepp {
    namespace sqlite3 {

        enum class progress_action {
            CONTINUE = 0,
            ABORT = 1
        };

        int progress_handler_func(void *handle);

        struct progress_handle {
            virtual progress_action notify() = 0;
        };

        template <class T>
        class progress_handler;

        template <class T>
        expected<progress_handler<T>> make_progress_handler(T functor);

        template <class T>
        class progress_handler : public progress_handle {
        public:
            progress_action notify() override final { return functor(); }

        private:

        private:
            T functor;
        };

    }
}