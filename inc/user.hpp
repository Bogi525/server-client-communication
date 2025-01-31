#ifndef _user_hpp_
#define _user_hpp_

#include <iostream>

class User {
public:

    User(std::string, std::string);

    std::string getUsername();
    std::string getPassword();

private:

    std::string username;
    std::string password;

};


#endif