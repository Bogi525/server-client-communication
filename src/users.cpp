#include "../inc/users.hpp"
#include <filesystem>

#define FILEPATH "users.csv"

Users::Users() : nullUser("/NULLUSERNAME", "/NULLPASSWORD") {

    std::fstream file(FILEPATH, std::ios_base::in);

    if (!file) {
        std::cout << "Error: File couldn't open.\n";
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    }

    int numOfEntries;

    file >> numOfEntries;

    for (int i = 0; i < numOfEntries; i++) {

        std::string line;

        file >> line;

        std::string username = "", password = "";

        int j = 0;

        while (line[j] != ',') {
            username += line[j++];
        }

        j++;

        while (j < line.size()) {
            password += line[j++];
        }

        User newUser(username, password);
        
        users.push_back(newUser);

    }

    file.close();

}

std::vector<User> Users::getAllUsers() {
    return users;
}

User Users::getUser(std::string username) {

    if (username == "/NULLUSERNAME") return nullUser;

    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) return users[i];
    }

    return nullUser;
}

bool Users::createUser(std::string username, std::string password) {

    if (username == "/NULLUSERNAME") return false;

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
    
    std::fstream file("users.csv", std::ios_base::app);

    file << '\n' << username << "," << password;

    file.close();

    return true;
}