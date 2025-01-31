#include <chrono>
#include <iostream>
#include <thread>
#include <map>
#include "../inc/logEntry.hpp"
#include "../inc/user.hpp"
#include "../inc/users.hpp"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define PRIVATE_IP "192.168.0.17"

int old_main() {
    try {

        vector<LogEntry> log;

        asio::io_context io_context;

        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345));

        std::cout << "Server is listening on port 12345...\n";

        bool finished = false;

        while (!finished) {
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

            Users users;

            bool found = false;
            //User curr_user;

            // for (User user: registered_users) {

            //     string curr_ip = socket.remote_endpoint().address().to_string();

            //     if (curr_ip == user.getUserIp()) {
            //         found = true;
            //         curr_user = user;
            //         break;
            //     } 
            // }

            // // Delete later
            // found = true;
            // curr_user = User("abc", "abc", "abc");

            while (!found) {
                message = "RequestUsername";
                asio::write(socket, asio::buffer(message));

                data_length = socket.read_some(asio::buffer(incoming_data));


            }

            if (found) {
                std::cout << "Asking for password...\n";
                message = "Login";

                asio::write(socket, asio::buffer(message));
                for (int i = 0; i < 3; i++) {
                    data_length = socket.read_some(asio::buffer(incoming_data));

                    //if (std::string(incoming_data, data_length) == curr_user.getPassword()) {
                        std::cout << "Client input: " << std::string(incoming_data, data_length) << '\n';
                        std::cout << "Correct password!";

                        message = "Correct";

                        asio::write(socket, asio::buffer(message));

                        break;
                    //}
                    //else if (i != 2) {
                        std::cout << "Client input: " << std::string(incoming_data, data_length) << '\n';
                        std::cout << 2 - i << " more tries.\n";

                        message = "Wrong";

                        asio::write(socket, asio::buffer(message));

                    //} else {
                        finished = true;
                        socket.close();
                    //}
                }  
            }

            std::cout << "\nSession successfully acknowledged!\nChat:\n";

            while(!finished) {
                data_length = socket.read_some(asio::buffer(incoming_data));
                LogEntry newLogEntry("User", string(incoming_data, data_length));
                newLogEntry.print();

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

void establishConnection(asio::io_context& io_context, asio::ip::tcp::acceptor& acceptor) {
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
}

int main() {
     try {
        Users users;

        asio::io_context io_context;

        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345));

        std::cout << "Server is listening on port 12345...\n";

        bool finished = false;

        while (!finished) {

            establishConnection(io_context, acceptor);

            // TODO - userChoice (login/register)
            // TODO - login
            // TODO - or register
            // TODO - messaging

            bool found;
        }
     } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
     }
}