#include <iostream>
#include "../inc/logEntry.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define SERVER_IP "192.168.0.17"
#define LOCALHOST_IP "127.0.0.1"


int main() {
    try {

        // Initializing data
        std::string server_ip = LOCALHOST_IP;

        std::string output_message = "";

        char incoming_data[1024];
        int data_length = 0;
        std::string incoming_message = "";

        asio::io_context io_context;

        asio::ip::tcp::socket socket(io_context);
        
        unsigned short server_port = 12345;

        asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(server_ip, std::to_string(server_port));

        
        // Establishing TCP connection
        asio::connect(socket, endpoints);

        std::cout << "Connected to server: " << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << '\n';
        
        data_length = socket.read_some(asio::buffer(incoming_data));

        std::cout << "Received from server: \"" << std::string(incoming_data, data_length) << "\"\n";

        output_message = "Hello from client!";
        asio::write(socket, asio::buffer(output_message));

        std::cout << "Sent to server: \"" << output_message << "\"\n";

        bool finished = false;


        // User choice
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

            // Checking Password
            while (incoming_message == "Password") {
                
            }

        } else if (output_message == "Register") {

        }
        // TODO: Login/Register

        // TODO: Chat

        /*
        data_length = socket.read_some(asio::buffer(incoming_data));

        if (std::string(incoming_data, data_length) == "Login") {
            std::cout << "Insert password: ";

            for (int i = 0; i < 3; i++) {
                std::getline(std::cin, output_message);

                asio::write(socket, asio::buffer(output_message));

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
        }
        */
        

    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    system("pause");

    return 0;
}