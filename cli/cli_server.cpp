#include <iostream>
#include "server.hpp"
#include <thread>
#include <chrono>

int main () {
    try {
        server serv;
        serv.connect("127.0.0.1", 1237, 2);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::string message = "Hello, clients!";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::string response = serv.receive();
        std::cout << "Client message: " << response << std::endl;
        serv.send(message);
        serv.close();
        return 0;
    } catch (const std::exception& ex) {
        std::cout << "exception occurred: " << ex.what() << std::endl;
        return 1;
    }
}