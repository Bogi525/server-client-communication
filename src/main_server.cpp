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

        vector<LogEntry> log;

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

            std::cout << "\nSession successfully acknowledged!\nChat:\n";
            
            bool finished = false;

            while(!finished) {

                data_length = socket.read_some(asio::buffer(incoming_data));
                LogEntry newLogEntry("User", EntryType::EntryTypeMSG, string(incoming_data, data_length));
                std::cout << newLogEntry.getUser() << "(" << newLogEntry.getTime() << "): " << newLogEntry.getMessage() << '\n';

                log.push_back(newLogEntry);
            }

            socket.close();
            
        }

    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
    
    system("pause");

    return 0;
}