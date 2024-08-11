
#ifndef CHATAPPLICATION_SERVER_HPP
#define CHATAPPLICATION_SERVER_HPP

#include "tcp_server.hpp"
#include <memory>

class server {
    std::unique_ptr<tcp_server> _server;
public:
    server() = default;
    void connect(const char*, int, int);
    void send(const std::string&);
    std::string receive();
    void close();
};

#endif //CHATAPPLICATION_SERVER_HPP
