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
#include "../inc/server.hpp"

void checkpointCheck() {
    std::cout << "Checkpoint\n";
    system("pause");
}

int main() {
     try {
        Server::get().establishTCPConnection();

        Server::get().userChoice();

      //   // TODO - messaging

      //   std::cout << incoming_message << "\t(R)\n";
      //   checkpointCheck();

         system("pause");

     } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
     }
     
     return 0;
}