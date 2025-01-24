#ifndef _user_hpp_
#define _user_hpp_

#include <iostream>

using namespace std;

class User {
public:
    User() {};
    User(string, string, string);
    string getUsername();
    string getPassword();
    string getUserIp();
private:
    string username;
    string password;
    string user_ip;
};


#endif