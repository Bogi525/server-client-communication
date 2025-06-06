#ifndef _client_hpp_
#define _client_hpp_

#define ASIO_STANDALONE
#define DEBUG_MESSAGES

#include <iostream>
#include <string>
#include <asio.hpp>

#define LOCALHOST_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

class Client {
public:

    static Client& get() {
        static Client instance;
        return instance;
    }

    void establishTCPConnection();

    void userChoice();

    bool loginUser();

    void registerUser();

    void messaging();

private:

    Client();
    ~Client() = default;

    std::string receiveMessage();
    std::string sendMessage(std::string);

    std::string server_ip;

    std::string output_message;
    char incoming_data[BUFFER_SIZE];
    int data_length;
    std::string incoming_message;

    asio::io_context io_context;

    asio::ip::tcp::socket socket;

    unsigned short server_port;

    asio::ip::tcp::resolver resolver;
    asio::ip::basic_resolver_results<asio::ip::tcp> endpoints;
};

#endif