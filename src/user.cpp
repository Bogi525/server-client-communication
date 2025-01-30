#include "../inc/user.hpp"

User::User(string a, string b) {
    username = a;
    password = b;
}

string User::getUsername() {
    return username;
}

string User::getPassword() {
    return password;
}
