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


void Client::userChoice() {
    data_length = socket.read_some(asio::buffer(incoming_data));

    incoming_message = std::string(incoming_data, data_length);

    if (incoming_message != "Choose") {
        std::cout << "Error: Server sent unexpected message\n";
        system("pause");
    }
    do {
        std::cout << "Choose whether you want to login or register by typing:\n";
        std::cout << "\"Login\" or \"Register\": ";
        std::cin >> output_message;
    } while (output_message != "Login" && output_message != "Register");
    
    asio::write(socket, asio::buffer(output_message));

    if (output_message == "Login") { 
        loginUser();
    } else { 
        registerUser();
    }
}


bool Client::loginUser() {

    // Finding username
    bool userFound = false;

    while (!userFound) {

        data_length = socket.read_some(asio::buffer(incoming_data));
        incoming_message = std::string(incoming_data, data_length);

        std::cout << "Username: ";

        std::cin >> output_message;
        asio::write(socket, asio::buffer(output_message));

        data_length = socket.read_some(asio::buffer(incoming_data));
        incoming_message = std::string(incoming_data, data_length);

        if (incoming_message == "Password") {
            userFound = true;
        }
    }

    // Checking password
    int counter = 0;

    std::cout << "Password: ";

    while (incoming_message == "Password") {

        if (counter > 0) {
            std::cout << "Wrong password, try again (" << 3 - counter << " tries left): ";
        }

        std::cin >> output_message;
        asio::write(socket, asio::buffer(output_message));

        data_length = socket.read_some(asio::buffer(incoming_data));
        incoming_message = std::string(incoming_data, data_length);

        counter++;
    }

    if (incoming_message == "Denied") {

        std::cout << "You inserted wrong password 3 times. Quitting...";

        socket.close();

        system("pause");

        return false;
    }

    return true;
}


void Client::registerUser() {

}