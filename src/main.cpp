#include <iostream>
#include "../inc/logEntry.hpp"
#include <asio.hpp>

using asio::ip::tcp;

int main() {
    LogEntry* entry1 = new LogEntry("bla", EntryType::EntryTypeMSG, "blabla");
    
    int a;
    std::cin >> a;
    return 0;
}