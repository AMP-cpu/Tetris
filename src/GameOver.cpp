#include "../headers/GameOver.hpp"
#include "../headers/Tetris.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include <sstream>

void GameOver(sf::RenderWindow& window, sf::Font font, User& user, Score& score, bool& gameOver, bool& menu) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background/skullBackground.jpg")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    // Set the origin of the background sprite to its center
    backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2);

    // Set the position of the background sprite to the center of the window
    backgroundSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    
    // Game over text rendering
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over\nYour Score:\n\t\t" + std::to_string(user.getScore()) + "\n");

    // Calculate the position to center the text
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setPosition((window.getSize().x - textRect.width) / 2, cellSize);

    // Restart text rendering
    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press R to restart\nPress M to go to the Menu");
    restartText.setPosition((window.getSize().x - restartText.getLocalBounds().width) / 2, gameOverText.getPosition().y + textRect.height + 500); // Position it below the game over text

    // Clear the window
    window.clear();

    window.draw(backgroundSprite);
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
            } else if (event.key.code == sf::Keyboard::M) {
                menu = true;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}
