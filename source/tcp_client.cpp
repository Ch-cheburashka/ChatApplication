#include "tcp_client.hpp"
#include <csignal>

tcp_client::tcp_client(const char* address, int port): _address(address), _port(port) {}

void tcp_client::connect() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        throw std::logic_error("Failed to create the socket!\n");
    }
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    socklen_t size = sizeof(addr);
    if (inet_pton(AF_INET, _address, &(addr.sin_addr)) <= 0) {
        throw std::invalid_argument("Invalid address or address not supported!\n");
    }
    if (::connect(_socket, reinterpret_cast<const sockaddr*>(&addr), size) < 0) {
        throw std::logic_error("Failed to connect to the server!\n");
    }
}

void tcp_client::send(int, const char *message, int len) const {
    if (::send(_socket, message, len, 0) < 0) {
        throw std::logic_error("Failed to send a message to the server!\n");
    }
}

const char *tcp_client::receive(int) const {
    auto buffer = new char[1024];
    if (::recv(_socket, buffer, 1024, 0) < 0) {
        throw std::logic_error("Failed to receive a message from the server!\n");
    }
    return buffer;
}

void tcp_client::close() const {
    ::close(_socket);
}

tcp_client::~tcp_client() {
    if (_socket != INVALID_SOCKET) {
        this->close();
    }
}