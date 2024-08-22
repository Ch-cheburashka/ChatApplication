#include <iostream>
#include "server.hpp"
#include <thread>

int main () {
    try {
        server serv;
        serv.connect("127.0.0.1", 1289, 4);
        serv.close();
        return 0;
    } catch (const std::exception& ex) {
        std::cout << "exception occurred: " << ex.what() << std::endl;
        return 1;
    }
}