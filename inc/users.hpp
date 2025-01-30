#ifndef _users_hpp_
#define _users_hpp_

#include <iostream>
#include <fstream>
#include <vector>
#include "user.hpp"


class Users {
public:
    Users();

    //Users(const Users&) = delete;
    //Users& operator=(const Users&) = delete;
    
    User getUser(std::string username);
    bool createUser(std::string username, std::string password);
    
private:
    bool addUserToFile(std::string username, std::string password);
    std::vector<User> users;
    User nullUser;
};

#endif