#include "tcp_server.hpp"
#include <csignal>

static volatile sig_atomic_t flag = 0;

void signal_handler(int) {
    flag = 1;
}

tcp_server::tcp_server(const char* address, int port, int clients_number): _address(address), _port(port), _clients_number(clients_number) {}

void tcp_server::connect() {
    signal(SIGINT, signal_handler);
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

    for (;;) {
        int client_socket = accept(_lsocket, nullptr, nullptr);
        if (client_socket < 0) {
            throw std::logic_error("Failed to accept a request from client!\n");
        }
        std::cout << _threads.size() << "\n\n";
        _client_sockets.emplace_back(client_socket);
        _threads.emplace_back(std::thread(&tcp_server::handle_client, this, _client_sockets.size()-1));
        if (flag == 1) {
            std::cout << "signal caught\n";
            break;
        }
    }
}

void tcp_server::send(int client_index, const char* message, int len) const {
    if (::send(_client_sockets[client_index], message, len, 0) < 0) {
        throw std::logic_error("Failed to send a message to a client!\n");
    }
}

const char* tcp_server::receive(int client_index) const {
    auto buffer = new char[1024];
    if (::recv(_client_sockets[client_index], buffer, 1024, 0) < 0) {
        throw std::logic_error("Failed to receive a message from a client!\n");
    }
    return buffer;
}


void tcp_server::close() const {
    ::close(_lsocket);
    for (auto& it: _client_sockets) {
        ::close(it);
    }
}

tcp_server::~tcp_server() {
    this->close();
}

void tcp_server::handle_client(int client_index) const {
    signal(SIGINT, signal_handler);
    try {
        for (;;) {
            if (flag == 1) {
                std::cout << "signal caught\n";
                break;
            }
            const char* client_message = receive(client_index);
            if (strlen(client_message) == 0) break;
            std::cout << "Received from client: " << client_message << std::endl;

            send(client_index, client_message, static_cast<int>(strlen(client_message)));
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Exception in client handler: " << ex.what() << std::endl;
    }

}
