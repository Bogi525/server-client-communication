#include <iostream>
#include "../inc/logEntry.hpp"
#include "../inc/client.hpp"

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define LOCALHOST_IP "127.0.0.1"

int main() {
    try {

        Client::get().establishTCPConnection();

        Client::get().userChoice();

    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    system("pause");

    return 0;
}