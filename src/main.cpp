#include "../headers/Tetris.hpp"
#include "../headers/Globals.hpp"
#include <SFML/Graphics.hpp>
#include "../headers/User.hpp"
#include "../headers/Score.hpp"
#include <iostream>
#include <ostream>
#include <sstream>

int main() {
    sf::Font font;
    if (!font.loadFromFile("font/Arial.ttf")) {
        // Failed to load font, handle the error
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode((cols + 2) * cellSize + (cols + 2) * cellSize, (rows + 2) * cellSize), "SFML Grid");
    window.setVerticalSyncEnabled(true); // Enable VSync

    // Create User
    User user;

    // Create Pontuation object
    Score score;

    bool gameOver = false;

    while (window.isOpen()) {
        // Run Tetris game
        if (!gameOver)
            tetris(window, font, user, score, gameOver);

        // Game over text rendering
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("Game Over\nYour Score:\n" + std::to_string(user.getScore())+"\n");
        gameOverText.setPosition((window.getSize().x - gameOverText.getLocalBounds().width) / 2, (window.getSize().y - gameOverText.getLocalBounds().height) / 2);

        // Restart text rendering
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setCharacterSize(30);
        restartText.setFillColor(sf::Color::White);
        restartText.setString("Press R to restart");
        restartText.setPosition((window.getSize().x - restartText.getLocalBounds().width) / 2, gameOverText.getPosition().y + gameOverText.getLocalBounds().height + 20); // Position it below the game over text

        // Clear the window
        window.clear();

        // Draw game over text
        window.draw(gameOverText);

        // Draw restart text if the game is over
        if (gameOver)
            window.draw(restartText);

        // Display the window
        window.display();

        // Check for window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                // Restart the game if the user presses 'r' or escape
                if (event.key.code == sf::Keyboard::R) {
                    user.reset();
                    score.reset();
                    gameOver = false;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
    }

    return 0;
}
