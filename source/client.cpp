#include "client.hpp"

void client::connect(const char* address, int port) {
    _client = std::make_unique<tcp_client>(address, port);
    _client->connect();
}

void client::send(const std::string& message) {
    _client->send(message.c_str(), static_cast<int>(message.length()));
}

std::string client::receive() {
    return _client->receive();
}

void client::close() {
    _client->close();
    _client.reset();
}


