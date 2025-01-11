#include <iostream>
#include "../inc/logEntry.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


int main() {

    //Initialize an ASIO error 
    asio::error_code ec;
    
    asio::io_context context;

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("192.168.0.1", ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec) {
        std::cout << "Connected!\n";
    } else {
        std::cout << "Failed to connect.\n";
        std::cout << ec.message() << "\n";
    }
    
    system("pause");

    return 0;
}