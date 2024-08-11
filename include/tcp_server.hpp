#ifndef INCLUDE_SMART_POINTERS_TCP_SERVER_HPP
#define INCLUDE_SMART_POINTERS_TCP_SERVER_HPP

#include "i_client.hpp"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class tcp_server : public i_client {
    const char* _address;
    int _port;
    int _lsocket = -1;
    int _asocket = -1;
    int _clients_number;
public:
    tcp_server(const char*, int, int);

    ~tcp_server() override;

    tcp_server(const tcp_server&) = delete;
    tcp_server(tcp_server&&) = delete;
    tcp_server& operator=(const tcp_server&) = delete;
    tcp_server& operator=(tcp_server&&) = delete;


    void connect() override;
    void send(const char*, int) const override;
    [[nodiscard]] const char* receive() const override;
    void close() const override;
};

#endif //INCLUDE_SMART_POINTERS_TCP_SERVER_HPP
