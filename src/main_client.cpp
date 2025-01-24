#include <chrono>
#include <iostream>
#include <thread>
#include <chrono>
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

        char incoming_data[1024];
        int data_length = socket.read_some(asio::buffer(incoming_data));

        std::cout << "Received from server: \"" << std::string(incoming_data, data_length) << "\"\n";

        std::string message = "Hello from client!";
        asio::write(socket, asio::buffer(message));

        std::cout << "Sent to server: \"" << message << "\"\n";

        bool finished = false;

        data_length = socket.read_some(asio::buffer(incoming_data));

        if (std::string(incoming_data, data_length) == "Login") {
            std::cout << "Insert password: ";

            for (int i = 0; i < 3; i++) {
                std::getline(std::cin, message);

                asio::write(socket, asio::buffer(message));

                data_length = socket.read_some(asio::buffer(incoming_data));


                std::string incoming_message = std::string(incoming_data, data_length);
                std::cout << "From server: '" << incoming_message << "'\n";

                if (incoming_message == "Correct") {
                    std::cout << "Connected!\n";
                    break;
                } else if (i != 2) {
                    std::cout << 2 - i << " more tries.\n";
                    std::cout << "Try again: ";
                } else {
                    finished = true;
                    socket.close();
                    break;
                }
            }
        } else {
            // TODO - registration
        }

        if (!finished) {
            std::cout << "Type !finish to exit session.\n\
                Type anything else to send a message to server.\n";

            while(!finished) {

                std::cout << "Input: ";
                std::getline(std::cin, message);

                if (message.length() > 1024) {

                    cout << "Message must have less than 1024 characters!\n";
                    continue;

                } else if (message == "!finish") {
                    
                    cout << "Finishing communication!\n";
                    finished = true;
                    break;
                    
                } else {
                    asio::write(socket, asio::buffer(message));
                    std::cout << "Sent!\n";
                }
            }

            socket.close();
        }

        

    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    system("pause");

    return 0;
}