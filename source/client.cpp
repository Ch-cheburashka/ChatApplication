#include "client.hpp"

void client::connect(const char* address, int port) {
    _client = std::make_unique<tcp_client>(address, port);
    _client->connect();
}

void client::close() {
    _client->close();
    _client.reset();
}


