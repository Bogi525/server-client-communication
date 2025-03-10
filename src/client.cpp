#include "../inc/client.hpp"

Client::Client() : io_context(), socket(io_context), resolver(io_context) {
    server_ip = LOCALHOST_IP;

    output_message = "";
    data_length = 0;
    incoming_message = "";

    server_port = 12345;

    endpoints = resolver.resolve(server_ip, std::to_string(server_port));
}


void Client::establishTCPConnection() {
    asio::connect(socket, endpoints);

    std::cout << "Connected to server: " << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << '\n';

    data_length = socket.read_some(asio::buffer(incoming_data));

    std::cout << "Received from server: \"" << std::string(incoming_data, data_length) << "\"\n";

    output_message = "Hello from client!";
    asio::write(socket, asio::buffer(output_message));

    std::cout << "Sent to server: \"" << output_message << "\"\n";
}