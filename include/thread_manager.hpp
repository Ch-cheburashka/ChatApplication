#ifndef CHATAPPLICATION_THREAD_MANAGER_HPP
#define CHATAPPLICATION_THREAD_MANAGER_HPP

#include <thread>

class thread_manager {
    std::thread _thread;
public:
    explicit thread_manager(std::thread);

    thread_manager(const thread_manager&) = delete;
    thread_manager& operator=(const thread_manager&) = delete;

    thread_manager(thread_manager&&) noexcept;

    ~thread_manager();
};

#endif //CHATAPPLICATION_THREAD_MANAGER_HPP
