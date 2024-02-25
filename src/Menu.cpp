#include "../headers/Menu.hpp"
#include "../headers/Tetris.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include <sstream>

void Menu(sf::RenderWindow& window, sf::Font font, User& user, Score& score, bool& gameOver, bool& menu) {
    // Create text objects for menu options
    sf::Text singlePlayerText;
    singlePlayerText.setFont(font);
    singlePlayerText.setCharacterSize(30);
    singlePlayerText.setFillColor(sf::Color::White);
    singlePlayerText.setString("1. Single Player");
    singlePlayerText.setPosition(100, 100);

    sf::Text doublePlayerText;
    doublePlayerText.setFont(font);
    doublePlayerText.setCharacterSize(30);
    doublePlayerText.setFillColor(sf::Color::White);
    doublePlayerText.setString("2. Double Player");
    doublePlayerText.setPosition(100, 150);

        // Clear the window
        window.clear();

        // Draw menu options
        window.draw(singlePlayerText);
        window.draw(doublePlayerText);

        // Display the window
        window.display();

        // Check for window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                // Start single player mode if the user presses '1'
                if (event.key.code == sf::Keyboard::Num1) {
                    // Call function to start single player mode
                    // For now, let's just print a message
                    std::cout << "Starting Single Player Mode" << std::endl;
                    menu=false;
                    gameOver=false;
                }
                // Start double player mode if the user presses '2'
                else if (event.key.code == sf::Keyboard::Num2) {
                    // Call function to start double player mode
                    // For now, let's just print a message
                    std::cout << "Starting Double Player Mode" << std::endl;
                    menu=false;
                }
            }
            
        }
    
}
