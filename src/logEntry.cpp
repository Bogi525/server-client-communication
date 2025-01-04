#include "../inc/logEntry.hpp"

LogEntry::LogEntry(std::string usr, EntryType typ, std::string msg) {
    user = usr;
    type = typ;
    message = msg;
    time_t currTime;
    time(&currTime);
    std::cout << ctime(&currTime);
}