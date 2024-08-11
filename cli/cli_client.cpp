#include "client.hpp"
#include <thread>
#include <chrono>

int main() {
    try {
        client cl;
        cl.connect("127.0.0.1", 1237);
        std::string message = "Hello, server!";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        cl.send(message);
        std::cout << "Message sent!\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::string response = cl.receive();
        std::cout << "Server response: " << response << std::endl;
        cl.close();
        return 0;
    } catch (const std::exception& ex) {
        std::cout << "exception occurred: " << ex.what() << std::endl;
        return 1;
    }
}