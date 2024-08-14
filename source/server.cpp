#include "server.hpp"

void server::connect(const char* address, int port, int clients_number) {
    _server = std::make_unique<tcp_server>(address, port, clients_number);
    _server->connect();
}

void server::close() {
    _server->close();
    _server.reset();
    std::cout << "Closed!\n";
}


