#ifndef _server_hpp_
#define _server_hpp_

#define ASIO_STANDALONE

#include <vector>
#include <asio.hpp>
#include "logEntry.hpp"
#include "users.hpp"

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

class Server {
public:
    static Server& get() {
        static Server instance;
        return instance;
    }

    void establishTCPConnection();

private:
    Server();

    ~Server() = default;

    Users users;
    User connected_user;

    vector<LogEntry> log;

    std::string output_message;
    char incoming_data[BUFFER_SIZE];
    int data_length;
    std::string incoming_message;

    asio::io_context io_context;

    asio::ip::tcp::socket socket;

    asio::ip::tcp::acceptor acceptor;
};

#endif