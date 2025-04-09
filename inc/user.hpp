#ifndef _user_hpp_
#define _user_hpp_

#include <iostream>

#define NULL_DATA "/NULL/"

class User {
public:
    User();

    User(std::string, std::string);

    std::string getUsername();
    std::string getPassword();

private:
    std::string username;
    std::string password;

};

#endif