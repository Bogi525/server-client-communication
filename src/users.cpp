#include "../inc/users.hpp"

Users::Users() : nullUser("/NULLUSERNAME", "/NULLPASSWORD") {
    fstream file("users.csv", std::ios_base::in);

    std::string line;

    for (int i = 0; i < 2; i++) {
        file >> line;
        cout << line;
    }

    file.close();
}

User Users::getUser(std::string username) {
    if (username == "/NULLUSERNAME") return nullUser;

    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) return users[i];
    }

    return nullUser;
}

bool Users::createUser(std::string username, std::string password) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) return false;
    }

    if (addUserToFile(username,password)) {

        User newUser(username, password);
        users.push_back(newUser);

        return true;

    } else {

        std::cout << "Error: user couldn't be registered\n";
        return false; 

    }
}

bool Users::addUserToFile(std::string username, std::string password) {
    fstream file("users.csv", std::ios_base::app);

    file << '\n' << username << "," << password;

    file.close();

    return true;
}