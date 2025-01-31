#include "../inc/user.hpp"

User::User(std::string a, std::string b) {
    username = a;
    password = b;
}

std::string User::getUsername() {
    return username;
}

std::string User::getPassword() {
    return password;
}
