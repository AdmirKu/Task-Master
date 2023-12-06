#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// Helper function to hash a password using SHA-256
std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(
return ss.str();
}

class User {
public:
    std::string username;
    std::string hashedPassword;
    std::vector<Task> tasks;

    User(const std::string& name, const std::string& password) : username(name) {
        // Hash the password before storing it
        hashedPassword = hashPassword(password);
    }

    // Validate the entered password against the stored hashed password
    bool validatePassword(const std::string& enteredPassword) const {
        return hashPassword(enteredPassword) == hashedPassword;
    }

    // Other member functions as before...
};

// Function to check if a user exists in the users file
bool userExists(const std::string& username) {
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, line.find(',')) == username) {
            return true;
        }
    }
    return false;
}

// Function to load a user's hashed password from the users file
std::string loadUserPassword(const std::string& username) {
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, line.find(',')) == username) {
            return line.substr(line.find(',') + 1);
        }
    }
    return "";
}

// Function to create a new user and store their credentials
void createUser(const std::string& username, const std::string& password) {
    std::ofstream file("users.txt", std::ios::app);
    file << username << "," << hashPassword(password) << "\n";
    std::cout << "User account created successfully.\n";
}

// Function to authenticate a user
bool authenticateUser(User& user) {
    std::string enteredUsername, enteredPassword;

    std::cout << "Enter username: ";
    std::cin >> enteredUsername;

    // Check if the user exists
    if (!userExists(enteredUsername)) {
        std::cout << "User does not exist.\n";
        return false;
    }

    std::cout << "Enter password: ";
    std::cin >> enteredPassword;

    // Load the hashed password for the entered username
    std::string storedPassword = loadUserPassword(enteredUsername);

    // Validate the entered password
    if (user.validatePassword(enteredPassword)) {
        std::cout << "Authentication successful. Welcome, " << enteredUsername << "!\n";
        user.username = enteredUsername;
        return true;
    } else {
        std::cout << "Incorrect password.\n";
        return false;
    }
}

int main() {
    User currentUser("", "");  // Temporary user object to handle authentication

    int choice;
    do {
        std::cout << "\nTask Master - Welcome!\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Create New User\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (authenticateUser(currentUser)) {
                    // Load tasks for the authenticated user
                    currentUser.loadTasksFromFile(currentUser.username + "_tasks.txt");
                    // Continue with the main menu for task management
                    // ...
                }
                break;
            case 2: {
                std::string newUsername, newPassword;
                std::cout << "Enter new username: ";
                std::cin >> newUsername;
                if (!userExists(newUsername)) {
                    std::cout << "Enter password: ";
                    std::cin >> newPassword;
                    createUser(newUsername, newPassword);
                } else {
                    std::cout << "Username already exists. Please choose a different username.\n";
                }
                break;
            }
            case 3:
                std::cout << "Exiting Task Master. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
