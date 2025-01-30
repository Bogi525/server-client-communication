#include "../inc/logEntry.hpp"

LogEntry::LogEntry(std::string usr, std::string msg) {
    user = usr;
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

void LogEntry::print() {
    std::cout << this->user << " (" << this->timeSent << ") : " << this->message << '\n';
}