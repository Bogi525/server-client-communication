#include <iostream>

class Log {
public:
    bool removeAll();
    bool pushMessage(std::string message);
    bool editLastMessage(std::string message);
    bool archive(std::string achive);
    void print();
private:
    std::string filename = "log.txt";
};