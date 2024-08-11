#include "tcp_server.hpp"

tcp_server::tcp_server(const char* address, int port, int clients_number): _address(address), _port(port), _clients_number(clients_number) {}

void tcp_server::connect() {
    _lsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_lsocket < 0) {
        throw std::logic_error("Failed to create the socket!\n");
    }
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    socklen_t size = sizeof(addr);
    if (inet_pton(AF_INET, _address, &(addr.sin_addr)) <= 0) {
        throw std::invalid_argument("Invalid address or address not supported!\n");

    }
    if (bind(_lsocket, reinterpret_cast<const sockaddr*>(&addr), size) < 0) {
        throw std::logic_error("Failed to bind to the address!\n");
    }

    listen(_lsocket, _clients_number);

    std::cout << "Waiting for clients to connect.\n";

    _asocket = accept(_lsocket, nullptr, nullptr);

    if (_asocket < 0) {
        throw std::logic_error("Failed to accept a request from client!\n");
    }
}

void tcp_server::send(const char* message, int len) const {
    if (::send(_asocket, message, len, 0) < 0) {
        throw std::logic_error("Failed to send a message to a client!\n");
    }
}

const char* tcp_server::receive() const {
    auto buffer = new char [1024];
    if (::recv(_asocket, buffer, 1024, 0) < 0) {
        throw std::logic_error("Failed to receive a message from a client!\n");
    }
    return buffer;
}


void tcp_server::close() const {
    ::close(_lsocket);
    ::close(_asocket);
}

tcp_server::~tcp_server() {
    if (_asocket != INVALID_SOCKET && _lsocket != INVALID_SOCKET) {
        this->close();
    }
}


