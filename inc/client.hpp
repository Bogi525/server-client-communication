#ifndef _client_hpp_
#define _client_hpp_

#define ASIO_STANDALONE

#include <iostream>
#include <string>
#include <asio.hpp>



#define LOCALHOST_IP "127.0.0.1"

// singleton
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

private:
    Client();

    ~Client() = default;

    std::string server_ip;

    std::string output_message;
    char incoming_data[1024];
    int data_length;
    std::string incoming_message;

    asio::io_context io_context;

    asio::ip::tcp::socket socket;

    unsigned short server_port;

    asio::ip::tcp::resolver resolver;
    asio::ip::basic_resolver_results<asio::ip::tcp> endpoints;
};

#endif