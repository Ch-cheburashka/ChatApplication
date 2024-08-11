#ifndef CHATAPPLICATION_CLIENT_HPP
#define CHATAPPLICATION_CLIENT_HPP

#include "tcp_client.hpp"
#include <memory>

class client {
    std::unique_ptr<tcp_client> _client;
public:
    client() = default;

    void connect(const char*, int);
    void send(const std::string&);
    std::string receive();
    void close();
};

#endif //CHATAPPLICATION_CLIENT_HPP
