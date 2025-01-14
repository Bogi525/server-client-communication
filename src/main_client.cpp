#include <chrono>
#include <iostream>
#include <thread>
#include "../inc/logEntry.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define IP_DEST "93.184.216.34"


int main() {

    // Initialize an ASIO error 
    asio::error_code ec;
    
    asio::io_context context;

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(IP_DEST, ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);



    if (!ec) {
        std::cout << "Connected!\n";
    } else {
        std::cout << "Failed to connect.\n";
        std::cout << ec.message() << "\n";
    }

    if (socket.is_open()) {
        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        size_t bytes = socket.available();
        std::cout << "Bytes Available: " << bytes << std::endl;

        if (bytes > 0) {
            std::vector<char> vBuffer(bytes);
            socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

            for (auto c: vBuffer)
                std::cout << c;
        }
    }

    
    
    system("pause");

    return 0;
}