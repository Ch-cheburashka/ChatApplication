#ifndef CHATAPPLICATION_TCP_SERVER_HPP
#define CHATAPPLICATION_TCP_SERVER_HPP

#include "i_client.hpp"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <list>
#include "thread_manager.hpp"
#include <vector>
#include <mutex>

class tcp_server : public i_client {
    const char* _address;
    int _port;
    int _lsocket = -1;
    int _clients_number;
    std::vector<int> _client_sockets;
    std::list<thread_manager> _threads;
    mutable std::mutex _clients_sockets_mutex;
public:
    tcp_server(const char*, int, int);

    ~tcp_server() override;

    tcp_server(const tcp_server&) = delete;
    tcp_server(tcp_server&&) = delete;
    tcp_server& operator=(const tcp_server&) = delete;
    tcp_server& operator=(tcp_server&&) = delete;


    void connect() override;
    void send(int, const char*, int) const override;
    [[nodiscard]] const char* receive(int) const override;
    void close() const override;
    void handle_client(int) const;
};

#endif //CHATAPPLICATION_TCP_SERVER_HPP
