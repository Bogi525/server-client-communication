#ifndef _log_entry_hpp_
#define _log_entry_hpp_

#include <iostream>
#include <ctime>

using namespace std;

enum EntryType { MSG, CMD };

class LogEntry {
    
public:
    LogEntry(string usr, EntryType typ, string msg);
private:
    string user;
    int timeSent;
    EntryType type;
    string message;
};

#endif