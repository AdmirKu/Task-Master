#include <iostream>
#include <vector>
#include <algorithm>

class Task {
public:
    std::string description;
    bool completed;

    Task(const std::string& desc) : description(desc), completed(false) {}
};

class User {
public:
    std::string username;
    std::vector<Task> tasks;

    User(const std::string& name) : username(name) {}

    void addTask(const std::string& desc) {
        tasks.emplace_back(desc);
    }

    void viewTasks() {
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
};

int main() {
    User currentUser("John Doe");

    // Menu-driven interface
    int choice;
    do {
        std::cout << "\nTask Master - Welcome, " << currentUser.username << "!\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Complete Task\n";
        std::cout << "4. Exit\n";
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
            std::cout << "Exiting Task Master. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
