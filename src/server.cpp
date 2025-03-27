#include "../inc/server.hpp"

Server::Server() : io_context(), socket(io_context), acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), SERVER_PORT)) {
    
    output_message = "";
    data_length = 0;
    incoming_message = "";

    std::cout << "Server is listening on port 12345...\n";
}

void Server::establishTCPConnection() {
    acceptor.accept(socket);

    std::cout << "Accepted connection from: "
        << socket.remote_endpoint().address().to_string()
        << '\n';

    output_message = "Hello from server!";
    asio::write(socket, asio::buffer(output_message));

    std::cout << "Sent to client: \"" << output_message << "\"\n";

    data_length = socket.read_some(asio::buffer(incoming_data));

    std::cout << "Received from client: \"" << std::string(incoming_data, data_length) << "\"\n";
}