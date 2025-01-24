#include "../inc/user.hpp"

User::User(string a, string b, string c) {
    username = a;
    password = b;
    user_ip = c;
}

string User::getUsername() {
    return username;
}

string User::getPassword() {
    return password;
}

string User::getUserIp() {
    return user_ip;
}