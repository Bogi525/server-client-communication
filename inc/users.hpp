#ifndef _accounts_hpp_
#define _accounts_hpp_

#include <iostream>
#include <vector>
#include "user.hpp"


class Users {
public:
    Users();

    Users(const Users&) = delete;
    Users& operator=(const Users&) = delete;
    
    User getUser(std::string username);
    
private:
    std::vector<User> users;
};

#endif