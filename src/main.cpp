#include <iostream>
#include "../inc/logEntry.hpp"
#include <asio.hpp>


int main() {
    LogEntry* entry1 = new LogEntry("bla", EntryType::EntryTypeMSG, "blabla");
    
    asio::io_context io_context;
    std::cout << "ASIO setup successful!\n";

    int a;
    std::cin >> a;
    return 0;
}