#include "sqlitepp/sqlite3/progress_handler.hxx"


int sqlitepp::sqlite3::progress_handler_func(void *handle) {
    progress_handle *handle_ptr = reinterpret_cast<progress_handle*>(handle);
    return static_cast<int>(handle_ptr->notify());
}
