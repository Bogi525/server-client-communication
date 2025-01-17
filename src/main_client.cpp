#include <chrono>
#include <iostream>
#include <thread>
#include "../inc/logEntry.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define SERVER_IP "192.168.0.17"
#define LOCALHOST_IP "127.0.0.1"


int main() {
    try {

        asio::io_context io_context;

        asio::ip::tcp::socket socket(io_context);

        std::string server_ip = SERVER_IP;
        unsigned short server_port = 12345;

        asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(server_ip, std::to_string(server_port));
        asio::connect(socket, endpoints);

        std::cout << "Connected to server: " << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << '\n';

        std::string message = "Hello from client!";
        asio::write(socket, asio::buffer(message));

        std::cout << "Sent to server: \"" << message << "\"\n";

        char incoming_data[1024];
        int data_length = socket.read_some(asio::buffer(incoming_data));

        std::cout << "Received from server: \"" << std::string(incoming_data, data_length) << "\"\n";

        std::string output_message;
        bool finished = false;

        while(!finished) {
            std::cout << "Input:";
            std::getline(std::cin, output_message);
            if (output_message.length() > 1024) {
                cout << "Message must have less than 1024 characters!\n";
                continue;
            } else if (output_message == "!finish") {
                cout << "Finishing communication!\n";
                finished = true;
                break;
            } else {
                asio::write(socket, asio::buffer(output_message));
                std::cout << "Sent!\n";
            }
        }

        socket.close();

        // // Initalizing ASIO error and context
        // asio::error_code ec;
        // asio::io_context context;

        // // Set the socket for IPv4 communication
        // asio::ip::udp::socket socket(context);
        // socket.open(asio::ip::udp::v4());

        // // Allow LAN broadcast communication
        // asio::socket_base::broadcast option(true);
        // socket.set_option(option);

        // // Set up a broadcast endpoint
        // asio::ip::udp::endpoint broadcast_endpoint(asio::ip::address_v4::broadcast(), 12345);

        // // Broadcasting the message across LAN
        // std::string messageToSend = "This is a broadcast message. Yippie!";
        // socket.send_to(asio::buffer(messageToSend), broadcast_endpoint);
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
    

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
    //}

    system("pause");

    return 0;
}