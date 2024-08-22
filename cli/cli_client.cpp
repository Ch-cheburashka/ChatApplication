#include "client.hpp"
#include <thread>

int main() {
    try {
        client cl;
        cl.connect("127.0.0.1", 1289);
        cl.close();
        return 0;
    } catch (const std::exception& ex) {
        std::cout << "exception occurred: " << ex.what() << std::endl;
        return 1;
    }
}