#include "../headers/Tetris.hpp"
#include "../headers/Globals.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>

int main() {

    sf::Font font;
    if (!font.loadFromFile("font/Arial.ttf")) {
        // Failed to load font, handle the error
        std::cerr << "Failed to load font" << std::endl;
    }
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode((cols + 2) * cellSize + (cols+ 2 ) * cellSize, (rows + 2) * cellSize), "SFML Grid");
    window.setVerticalSyncEnabled(true); // Enable VSync

    tetris(window, font);
    
    // Game over text rendering
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition((window.getSize().x - gameOverText.getLocalBounds().width) / 2, (window.getSize().y - gameOverText.getLocalBounds().height) / 2);

    // Clear the window
    window.clear();

    // Draw game over text
    window.draw(gameOverText);

    // Display the window
    window.display();

    // Wait for a short while before closing
    sf::sleep(sf::seconds(4));
}