#ifndef CHATAPPLICATION_TCP_CLIENT_HPP
#define CHATAPPLICATION_TCP_CLIENT_HPP

#include "i_client.hpp"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "thread_manager.hpp"
#include <memory>

class tcp_client : public i_client {
    const char* _address;
    int _port;
    int _socket = INVALID_SOCKET;
    std::unique_ptr<thread_manager> _send_thread;
    std::unique_ptr<thread_manager> _receive_thread;
    mutable std::mutex _send_mutex;
    mutable std::mutex _receive_mutex;
    mutable std::mutex _socket_mutex;


public:
    tcp_client(const char*, int);

    ~tcp_client() override;

    void connect() override;
    void send(int, const char*, int) const override;
    [[nodiscard]] const char* receive(int) const override;
    void receive_continuously() const;
    void send_continuously() const;
    void close() const override;
};


#endif //CHATAPPLICATION_TCP_CLIENT_HPP
