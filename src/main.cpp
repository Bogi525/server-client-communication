#include <iostream>
#include "../inc/logEntry.hpp"
//#include "../lib/asio/asio.hpp"

using namespace std;

int main() {
    LogEntry* entry1 = new LogEntry("bla", EntryType::MSG, "blabla");
    int a;
    cin >> a;
    return 0;
}