#include "../inc/client.hpp"

Client::Client() : io_context(), socket(io_context), resolver(io_context) {
    server_ip = LOCALHOST_IP;

    output_message = "";
    data_length = 0;
    incoming_message = "";

    server_port = SERVER_PORT;

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

    std::string choiceString = "Register Request";
    
    do {
        std::cout << "Choose whether you want to login or register by typing:\n";
        std::cout << "\"Login\" or \"Register\": ";
        std::cin >> choiceString;
    } while (choiceString != "Login" && choiceString != "Register");

    if (choiceString == "Login") output_message = "Login Request";
    
    asio::write(socket, asio::buffer(output_message));

    if (output_message == "Login Request") { 
        loginUser();
    } else { 
        registerUser();
    }
}


bool Client::loginUser() {
    std::cout << "Logging in...\n";

    do {

        data_length = socket.read_some(asio::buffer(incoming_data));
        incoming_message = std::string(incoming_data, data_length);

        if (incoming_message == "Username Request") {

            std::cout << "Username: ";

            std::cin >> output_message;
            asio::write(socket, asio::buffer(output_message));

        } else if (incoming_message == "Password Request") {

            std::cout << "Password: ";

            std::cin >> output_message;
            asio::write(socket, asio::buffer(output_message));

        } else if (incoming_message == "Denied") {

            std::cout << "You inserted wrong password 3 times. Quitting...\n";
            
            return false;
        } else if (incoming_message == "Accepted") {
            break;
        } else throw std::exception();

    } while (true);

    return true;
}


void Client::registerUser() {
    std::cout << "Registering...\n";
}