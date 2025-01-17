#include "../inc/logEntry.hpp"

LogEntry::LogEntry(std::string usr, EntryType typ, std::string msg) {
    user = usr;
    type = typ;
    message = msg;
    time_t currTime;
    time(&currTime);
    timeSent = string(ctime(&currTime));
    timeSent.resize(timeSent.size() - 1);
}

string LogEntry::getUser() {
    return user;
}

string LogEntry::getTime() {
    return timeSent;
}

string LogEntry::getMessage() {
    return message;
}