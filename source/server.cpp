#include "server.hpp"

void server::connect(const char* address, int port, int clients_number) {
    _server = std::make_unique<tcp_server>(address, port, clients_number);
    _server->connect();
}

void server::send(const std::string& message) {
    _server->send(message.c_str(), static_cast<int>(message.length()));
}

std::string server::receive() {
    return _server->receive();
}

void server::close() {
    _server->close();
    _server.reset();
}


