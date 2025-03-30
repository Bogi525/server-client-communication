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


void Server::userChoice() {
    bool userChoice = false;

    output_message = "Choose";
    asio::write(socket, asio::buffer(output_message));

    data_length = socket.read_some(asio::buffer(incoming_data));
    incoming_message = std::string(incoming_data, data_length);

    if (incoming_message == "Login Request") userChoice = true;

    if (userChoice) {
        loginUser();
    } else {
        registerUser();
    }
}


bool Server::loginUser() {
    bool userFound = false;

    while (userFound == false) {

        output_message = "Username Request";
        asio::write(socket, asio::buffer(output_message));

        data_length = socket.read_some(asio::buffer(incoming_data));
        incoming_message = std::string(incoming_data, data_length);

        for (User user: users.getAllUsers()) {
            if (incoming_message == user.getUsername()) {

                connected_user = user;
                userFound = true;

            }
        }
    }

    std::cout << "Username: " << connected_user.getUsername() << '\n';

    // Password check
    bool correctPassword = false;

    int counter = 0;

    while (!correctPassword && counter < 3) {

        output_message = "Password Request";
        asio::write(socket, asio::buffer(output_message));

        data_length = socket.read_some(asio::buffer(incoming_data));
        incoming_message = std::string(incoming_data, data_length);

        if (incoming_message == connected_user.getPassword()) {
            correctPassword = true;
            break;
        }

        counter++;
    }


    // User wrote wrong password 3 times
    if (!correctPassword) {

        output_message = "Denied";
        asio::write(socket,asio::buffer(output_message));

        socket.close();

        std::cout << "Wrong password 3 times\n";

        return false;
    }


    // Correct password
    output_message = "Accepted";
    asio::write(socket, asio::buffer(output_message));

    return true;
}


void Server::registerUser() {

}