#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Task {
public:
    std::string description;
    bool completed;

    Task(const std::string& desc) : description(desc), completed(false) {}
};

class TaskMasterGUI {
public:
    TaskMasterGUI() : window(sf::VideoMode(800, 600), "Task Master GUI") {
        font.loadFromFile("arial.ttf"); // Load a font, replace with your own font file
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        addButton("Add Task", sf::Vector2f(50, 50));
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    std::vector<Task> tasks;
    std::vector<sf::RectangleShape> buttons;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }

    void update() {
        // Update logic goes here
    }

    void render() {
        window.clear(sf::Color::White);

        // Render tasks
        for (size_t i = 0; i < tasks.size(); ++i) {
            text.setString(tasks[i].description);
            text.setPosition(100, 100 + i * 30);
            window.draw(text);
        }

        // Render buttons
        for (const auto& button : buttons) {
            window.draw(button);
        }

        window.display();
    }

    void addButton(const std::string& label, const sf::Vector2f& position) {
        sf::RectangleShape button(sf::Vector2f(100, 40));
        button.setFillColor(sf::Color::Green);
        button.setPosition(position);

        sf::Text buttonText(label, font, 16);
        buttonText.setPosition(position.x + 10, position.y + 10);
        buttonText.setFillColor(sf::Color::White);

        buttons.push_back(button);

        // You can handle button click logic here
    }

    void handleMouseClick(float x, float y) {
        // Check if any button was clicked and handle the click
        for (const auto& button : buttons) {
            sf::FloatRect bounds = button.getGlobalBounds();
            if (bounds.contains(x, y)) {
                handleButtonClick(button);
                return;
            }
        }
    }

    void handleButtonClick(const sf::RectangleShape& button) {
        // Handle button click logic
        if (button.getFillColor() == sf::Color::Green) {
            // For example, add a new task when the "Add Task" button is clicked
            tasks.emplace_back("New Task");
        }
    }
};

int main() {
    TaskMasterGUI taskMaster;
    taskMaster.run();

    return 0;
}
