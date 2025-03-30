#include <iostream>
#include "../inc/logEntry.hpp"
#include "../inc/client.hpp"

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define LOCALHOST_IP "127.0.0.1"

int main() {
    try {

        Client::get().establishTCPConnection();

        Client::get().userChoice();
        
        // // TODO: Chat
        // if (!finished) {

        //     std::cout << "Type !finish to exit session.\n";
        //     std::cout << "Type anything else to send a message to server.\n";

        //     while(!finished) {

        //         std::cout << "Input: ";
        //         std::getline(std::cin, output_message);

        //         if (output_message.length() > 1024) {

        //             cout << "Message must have less than 1024 characters!\n";
        //             continue;

        //         } else if (output_message == "!finish") {
                    
        //             cout << "Finishing communication!\n";
        //             finished = true;
        //             break;
                    
        //         } else {
        //             asio::write(socket, asio::buffer(output_message));
        //             std::cout << "Sent!\n";
        //         }
        //     }

        //     socket.close();
        // }

    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    system("pause");

    return 0;
}