#ifndef _log_entry_hpp_
#define _log_entry_hpp_

#include <iostream>
#include <ctime>

using namespace std;

class LogEntry {
    
public:
    LogEntry(string usr, string msg);
    string getUser();
    string getTime();
    string getMessage();
private:
    string user;
    string timeSent;
    string message;
};

#endif