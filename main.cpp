#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Task {
public:
    std::string description;
    bool completed;

    Task(const std::string& desc, bool comp = false) : description(desc), completed(comp) {}

    // Convert task to a string for storage in a file
    std::string toString() const {
        return description + "," + (completed ? "1" : "0");
    }
};

class User {
public:
    std::string username;
    std::vector<Task> tasks;

    User(const std::string& name) : username(name) {}

    void addTask(const std::string& desc) {
        tasks.emplace_back(desc);
    }

    void viewTasks() const {
        std::cout << "Tasks for user " << username << ":\n";
        for (const auto& task : tasks) {
            std::cout << "- " << task.description << (task.completed ? " (Completed)" : "") << "\n";
        }
    }

    void completeTask(const std::string& desc) {
        auto it = std::find_if(tasks.begin(), tasks.end(), [&desc](const Task& task) {
            return task.description == desc;
        });

        if (it != tasks.end()) {
            it->completed = true;
            std::cout << "Task '" << desc << "' marked as completed.\n";
        } else {
            std::cout << "Task not found.\n";
        }
    }

    // Save user's tasks to a file
    void saveTasksToFile(const std::string& filename) const {
        std::ofstream file(filename);

        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.toString() << "\n";
            }
            std::cout << "Tasks saved to file.\n";
        } else {
            std::cerr << "Unable to open file for writing.\n";
        }
    }

    // Load user's tasks from a file
    void loadTasksFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (file.is_open()) {
            tasks.clear(); // Clear existing tasks
            std::string line;
            while (std::getline(file, line)) {
                // Split the line into description and completion status
                size_t commaPos = line.find(',');
                if (commaPos != std::string::npos && commaPos < line.length() - 1) {
                    std::string desc = line.substr(0, commaPos);
                    bool comp = line.substr(commaPos + 1) == "1";
                    tasks.emplace_back(desc, comp);
                }
            }
            std::cout << "Tasks loaded from file.\n";
        } else {
            std::cerr << "Unable to open file for reading.\n";
        }
    }
};

int main() {
    User currentUser("John Doe");

    // Load tasks from a file
    currentUser.loadTasksFromFile("tasks.txt");

    // Menu-driven interface
    int choice;
    do {
        std::cout << "\nTask Master - Welcome, " << currentUser.username << "!\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Complete Task\n";
        std::cout << "4. Save Tasks\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string taskDesc;
            std::cout << "Enter task description: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, taskDesc);
            currentUser.addTask(taskDesc);
            break;
        }
        case 2:
            currentUser.viewTasks();
            break;
        case 3: {
            std::string taskDesc;
            std::cout << "Enter task description to mark as completed: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, taskDesc);
            currentUser.completeTask(taskDesc);
            break;
        }
        case 4:
            // Save tasks to a file
            currentUser.saveTasksToFile("tasks.txt");
            break;
        case 5:
            std::cout << "Exiting Task Master. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
