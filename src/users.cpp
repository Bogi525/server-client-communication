#include "../inc/users.hpp"

Users::Users() {
    User nullUser("/NULLUSERNAME", "/NULLPASSWORD");
    users.push_back(nullUser);
}

User Users::getUser(std::string username) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) return users[i];
    }
    return users[0];
}