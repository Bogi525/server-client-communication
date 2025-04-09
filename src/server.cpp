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

    output_message = sendMessage("Hello from server!");

    std::cout << "Sent to client: \"" << output_message << "\"\n";

    receiveMessage();
    std::cout << "Received from client: \"" << incoming_message << "\"\n";
}


void Server::userChoice() {
    bool userChoice = false;

    sendMessage("Choose");

    receiveMessage();

    if (incoming_message == "Login Request") userChoice = true;

    if (userChoice) {
        loginUser();
    } else {
        registerUser();
    }
}


bool Server::loginUser() {
    std::cout << "Logging in...\n";
    
    bool userFound = false;

    while (userFound == false) {

        sendMessage("Username Request");

        receiveMessage();

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

        sendMessage("Password Request");

        receiveMessage();

        if (incoming_message == connected_user.getPassword()) {
            correctPassword = true;
            break;
        }

        counter++;
    }


    // User wrote wrong password 3 times
    if (!correctPassword) {

        sendMessage("Denied");

        socket.close();

        std::cout << "Wrong password 3 times\n";

        return false;
    }


    // Correct password
    sendMessage("Accepted");

    return true;
}


void Server::registerUser() {
    std::cout << "Registering...\n";
    
    // Choosing a username
    sendMessage("Username Request");

    std::string wanted_username = NULL_DATA;

    while (true) {
        wanted_username = receiveMessage();
        
        bool userFound = false;
        for (User user: users.getAllUsers()) {
            if (user.getUsername() == wanted_username) {
                userFound = true;
                break;
            }
        }
        if (!userFound) break;
        else sendMessage("Username Already Used");
    }

    // Choosing a password
    sendMessage("Password Request");

    std::string wanted_password = receiveMessage();

    users.createUser(wanted_username, wanted_password);

    sendMessage("Accepted");
}

std::string Server::receiveMessage() {
    data_length = socket.read_some(asio::buffer(incoming_data));
    incoming_message = std::string(incoming_data, data_length);

    #ifdef DEBUG_MESSAGES
    std::cout << "\t - Message received: " << incoming_message << '\n';
    #endif

    return incoming_message;
}

std::string Server::sendMessage(std::string msg) {

    #ifdef DEBUG_MESSAGES
    std::cout << "\t - Message sent: " << msg << '\n';
    #endif

    asio::write(socket, asio::buffer(msg));
    return msg;
}