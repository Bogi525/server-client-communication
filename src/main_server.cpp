#include <chrono>
#include <iostream>
#include <thread>
#include "../inc/logEntry.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define PRIVATE_IP "192.168.0.17"


int main() {
    try {

        asio::io_context io_context;

        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345));

        std::cout << "Server is listening on port 12345...\n";

        while (true) {
            asio::ip::tcp::socket socket(io_context);

            acceptor.accept(socket);

            std::cout << "Accepted connection from: "
                << socket.remote_endpoint().address().to_string()
                << '\n';

            std::string message = "Hello from server!";
            asio::write(socket, asio::buffer(message));

            std::cout << "Sent to client: \"" << message << "\"\n";

            char incoming_data[1024];
            int data_length = socket.read_some(asio::buffer(incoming_data));

            std::cout << "Received from client: \"" << std::string(incoming_data, data_length) << "\"\n";

            socket.close();
        }



    //     // Initalizing ASIO error and context
    //     asio::error_code ec;
    //     asio::io_context context;

    //     asio::ip::udp::socket socket(context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 12345));

    //     char data[1024];
    //     asio::ip::udp::endpoint sender_endpoint;

    //     std::cout << "Server is starting to listen for incoming traffic on port 12345";

    //     while(true) {
    //         std::size_t bytes = socket.receive_from(asio::buffer(data, sizeof(data)),sender_endpoint);
    //         std::string message(data, bytes);
    //         std::cout << "Received message from \"" << sender_endpoint.address() << "\", size = " << bytes << ":\n";
    //         std::cout << message << '\n';
    //     }
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
    
    system("pause");

    return 0;

    // // Initialize an ASIO error 
    // asio::error_code ec;
    
    // asio::io_context context;

    // asio::ip::tcp::endpoint endpoint(asio::ip::make_address(IP_DEST, ec), 80);

    // asio::ip::tcp::socket socket(context);

    // socket.connect(endpoint, ec);



    // if (!ec) {
    //     std::cout << "Connected!\n";
    // } else {
    //     std::cout << "Failed to connect.\n";
    //     std::cout << ec.message() << "\n";
    // }

    // if (socket.is_open()) {
    //     std::string sRequest =
    //         "GET /index.html HTTP/1.1\r\n"
    //         "Host: example.com\r\n"
    //         "Connection: close\r\n\r\n";

    //     socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

    //     std::this_thread::sleep_for(std::chrono::milliseconds(200));

    //     size_t bytes = socket.available();
    //     std::cout << "Bytes Available: " << bytes << std::endl;

    //     if (bytes > 0) {
    //         std::vector<char> vBuffer(bytes);
    //         socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

    //         for (auto c: vBuffer)
    //             std::cout << c;
    //     }
    // }
    
    
}