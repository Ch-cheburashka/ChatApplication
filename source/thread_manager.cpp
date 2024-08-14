#include "thread_manager.hpp"

thread_manager::thread_manager(std::thread thread): _thread(std::move(thread)) {}

thread_manager::thread_manager(thread_manager &&other) noexcept {
    _thread = std::move(other._thread);
}

thread_manager::~thread_manager() {
    _thread.join();
}

