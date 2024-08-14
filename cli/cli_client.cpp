#include "client.hpp"
#include <thread>
#include <csignal>
#include <chrono>

static volatile sig_atomic_t flag = 0;

void signal_handler(int) {
    flag = 1;
}

int main(int argc, char** argv) {
    signal(SIGINT, signal_handler);
    try {
        client cl;
        cl.connect("127.0.0.1", 1247);
        while (true) {
            if (flag == 1) {
                break;
            }
            std::string message = std::string(argv[1]);
            cl.send(message);
            std::string response = cl.receive();
            std::cout << "Server response: " << response << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        cl.close();
        return 0;
    } catch (const std::exception& ex) {
        std::cout << "exception occurred: " << ex.what() << std::endl;
        return 1;
    }
}