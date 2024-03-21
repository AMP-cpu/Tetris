#include "../headers/Menu.hpp"
#include "../headers/Tetris.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include <sstream>

void Menu(sf::RenderWindow& window, sf::Font font, bool& gameOver, bool& menu, int& network) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background/TetrisBackground.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    
    // Create text objects for menu options
    sf::Text singlePlayerText;
    singlePlayerText.setFont(font);
    singlePlayerText.setCharacterSize(30);
    singlePlayerText.setFillColor(sf::Color::White);
    singlePlayerText.setString("1. Single Player");
    singlePlayerText.setPosition(100, 100);

    sf::Text hostDoublePlayerText;
    hostDoublePlayerText.setFont(font);
    hostDoublePlayerText.setCharacterSize(30);
    hostDoublePlayerText.setFillColor(sf::Color::White);
    hostDoublePlayerText.setString("2. Host Double Player");
    hostDoublePlayerText.setPosition(100, 150);

    sf::Text joinDoublePlayerText;
    joinDoublePlayerText.setFont(font);
    joinDoublePlayerText.setCharacterSize(30);
    joinDoublePlayerText.setFillColor(sf::Color::White);
    joinDoublePlayerText.setString("3. Join Double Player");
    joinDoublePlayerText.setPosition(100, 200);

        // Clear the window
        window.clear();

        // Draw menu options
        window.draw(backgroundSprite);
        window.draw(singlePlayerText);
        window.draw(hostDoublePlayerText);
        window.draw(joinDoublePlayerText);
        

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
                    network=0;
                }
                // Host double player mode if the user presses '2'
                else if (event.key.code == sf::Keyboard::Num2) {
                    // Call function to start double player mode
                    // For now, let's just print a message
                    std::cout << "Starting Double Player Mode" << std::endl;
                    menu=false;
                    gameOver=false;
                    network=1;
                }
                // Enter in another double player server if the user presses '3'
                else if (event.key.code == sf::Keyboard::Num3) {
                    // Call function to start double player mode
                    // For now, let's just print a message
                    std::cout << "Starting Double Player Mode" << std::endl;
                    menu=false;
                    gameOver=false;
                    network=2;
                }
            }
            
        }
    
}