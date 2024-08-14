#ifndef CHATAPPLICATION_TCP_CLIENT_HPP
#define CHATAPPLICATION_TCP_CLIENT_HPP

#include "i_client.hpp"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class tcp_client : i_client {
    const char* _address;
    int _port;
    int _socket = -1;
public:
    tcp_client(const char*, int);

    ~tcp_client() override;

    void connect() override;
    void send(int, const char*, int) const override;
    [[nodiscard]] const char* receive(int) const override;
    void close() const override;
};


#endif //CHATAPPLICATION_TCP_CLIENT_HPP
