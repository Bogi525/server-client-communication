#ifndef _log_entry_hpp_
#define _log_entry_hpp_

#include <iostream>
#include <ctime>

using namespace std;

enum EntryType { EntryTypeMSG, EntryTypeCMD };

class LogEntry {
    
public:
    LogEntry(string usr, EntryType typ, string msg);
    string getUser();
    string getTime();
    string getMessage();
private:
    string user;
    string timeSent;
    EntryType type;
    string message;
};

#endif