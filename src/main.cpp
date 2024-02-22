#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Grid.hpp"
#include "../headers/Blocs.hpp"
#include "../headers/Pieces.hpp"
#include "../headers/User.hpp"
#include <random> // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <chrono> // for timing
#include <algorithm>

int main() {
    // Load font for displaying cell values
    sf::Font font;
    if (!font.loadFromFile("font/Arial.ttf")) {
        // Failed to load font, handle the error
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode((cols + 2) * cellSize, (rows + 1) * cellSize), "SFML Grid");
    window.setVerticalSyncEnabled(true); // Enable VSync

    // Create User
    User user;

    // Create a grid object
    Grid<int> grid(rows + 1, cols + 2, 0);

    bool landed = true; // Flag to indicate if the current piece has landed
    bool firstPiece = true;

    std::vector<Block> pieceBlocks;
    Piece<Block> piece(pieceBlocks);

    // Set initial fall interval and velocity
    int fallInterval = 500; // in milliseconds
    unsigned int minInterval = 100; // in milliseconds
    int accelerationFactor = 10; // Adjust as needed

    // Initialize timing variables
    auto lastTime = std::chrono::steady_clock::now();
    auto currentTime = lastTime;
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        if (landed || firstPiece) {
            if(!firstPiece) {
                int numberOfLignes = 0;
                for(int i = piece.getHighestVerticalPosition(); i<=piece.getLowestVerticalPosition(); i++) {
                    if(grid.isLineComplete(i)) {
                        grid.eraseAndMoveLinesDown(i);
                        numberOfLignes++;
                    }    
                }
                user.increasePoints(numberOfLignes);
                std::cout<<"Pontos: "<<user.getPontuation()<<std::endl;
            }
            // Create a new piece with the chosen blocks
            Piece<Block> pieceT = Piece<Block>::generateRandomPiece();
            piece = pieceT.clone();
            piece.draw(window);
            landed = false; // Reset the landed flag
            
            firstPiece = false;

            // Reset timing variables
            lastTime = std::chrono::steady_clock::now();
        }

        // Update timing
        currentTime = std::chrono::steady_clock::now();
        timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

        // Add blocks to the piece based on the chosen piece number
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle keyboard input
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    piece.rotateClockwiseIfPossible(grid);
                } else if (event.key.code == sf::Keyboard::Left) {
                    piece.moveLeft(grid);
                } else if (event.key.code == sf::Keyboard::Right) {
                    piece.moveRight(grid);
                } else if (event.key.code == sf::Keyboard::Down) {
                    piece.moveDown(grid, &landed);
                }
            }
        }

        // Automatic downward movement
        if (timeDiff >= fallInterval) {
            piece.moveDown(grid, &landed);
            lastTime = std::chrono::steady_clock::now();
        }

        // Clear the window
        window.clear();

        // Draw the grid
        grid.draw(window, font, cellSize);

        // Draw the piece
        piece.draw(window);

        // Display the window
        window.display();

        // Increase fall velocity based on level
        fallInterval = std::max(minInterval, 500 - user.getLevel() * accelerationFactor);
    }

    return 0;
}
