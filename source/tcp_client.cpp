#include "tcp_client.hpp"
#include <csignal>

static volatile sig_atomic_t flag = 0;

void signal_handler(int) {
    flag = 1;
}

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

    _send_thread = std::make_unique<thread_manager>(std::thread(&tcp_client::send_continuously, this));
    _receive_thread = std::make_unique<thread_manager>(std::thread(&tcp_client::receive_continuously, this));
    for (;;) {
        if (flag == 1)
            break;
    }
}

void tcp_client::send(int, const char *message, int len) const {
    std::lock_guard<std::mutex> lock(_send_mutex);
    if (_socket < 0) {
        throw std::logic_error("Socket is invalid!\n");
    }
    if (len == 0) return;
    if (::send(_socket, message, len, 0) < 0) {
        throw std::logic_error("Failed to send a message to the server!\n");
    }
}

void tcp_client::send_continuously() const {
    try {
        for (;;) {
            if (flag == 1) {
                return;
            }
            std::string message;
            std::getline(std::cin, message);
            send(0, message.c_str(), static_cast<int>(message.length()));
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Exception while sending: " << ex.what() << std::endl;
    }
}

const char* tcp_client::receive(int) const {
    std::lock_guard<std::mutex> lock(_receive_mutex);
    if (_socket < 0) {
        throw std::logic_error("Socket is invalid!\n");
    }
    auto buffer = new char[1024];
    if (::recv(_socket, buffer, 1024, 0) < 0) {
        throw std::logic_error("Failed to receive a message from the server!\n");
    }
    buffer[strlen(buffer)] = '\0';
    return buffer;
}

void tcp_client::receive_continuously() const {
    try {
        for (;;) {
            if (flag == 1) {
                return;
            }
            const char* response = receive(0);
            std::cout << "\n >> " << response << "\n";
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Exception while receiving: " << ex.what() << std::endl;
    }
}

void tcp_client::close() const {
    std::lock_guard<std::mutex> lock(_socket_mutex);
    if (_socket >= 0) {
        ::close(_socket);
    }
}

tcp_client::~tcp_client() {
    if (_socket != INVALID_SOCKET) {
        this->close();
    }
}