#include "../inc/user.hpp"

User::User() {
    username = NULL_DATA;
    password = NULL_DATA;
}

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
