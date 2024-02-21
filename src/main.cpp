#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Grid.hpp"
#include "../headers/Blocs.hpp"
#include <random> // for std::random_device, std::mt19937, std::uniform_int_distribution

int main() {
    // Define grid parameters
    constexpr int cols = 10;
    constexpr int rows = 20;
    constexpr int cellSize = 40;

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

    // Create a grid object
    Grid<int> grid(rows + 1, cols + 2, 0);

    bool landed = true; // Flag to indicate if the current piece has landed

    std::vector<Block> pieceBlocks;
    Piece piece(pieceBlocks);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        if (landed) {
            for (const auto& block : piece.getBlocks()) {
                int row = block.getPosition().y / cellSize;
                int col = block.getPosition().x / cellSize;
                grid.set(row, col, 2); // Set the corresponding grid cell to 1 to indicate the block is occupied
                grid.setColor(row, col, block.getColor());
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 7); // Distribution for 7 Tetris pieces
            int pieceNumber = dis(gen);

            // Create a vector to hold blocks for the chosen piece
            std::vector<Block> pieceBlocks;

            // Add blocks to the piece based on the chosen piece number
            switch (pieceNumber) {
                case 1: // Straight piece (I)
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, 0), sf::Color::Cyan);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, 0), sf::Color::Cyan);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, 0), sf::Color::Cyan);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 6, 0), sf::Color::Cyan);
                    break;
                case 2: // L piece
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, 0), sf::Color::Blue);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize), sf::Color::Blue);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color::Blue);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), sf::Color::Blue);
                    break;
                case 3: // J piece
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, 0), sf::Color(255, 165, 0));
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize), sf::Color(255, 165, 0));
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color(255, 165, 0));
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), sf::Color(255, 165, 0));
                    break;
                case 4: // Square piece (O)
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, 0), sf::Color::Yellow);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, 0), sf::Color::Yellow);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color::Yellow);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), sf::Color::Yellow);
                    break;
                case 5: // S piece
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, 0), sf::Color::Green);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, 0), sf::Color::Green);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize), sf::Color::Green);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color::Green);
                    break;
                case 6: // T piece
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, 0), sf::Color(128, 0, 128));
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize), sf::Color(128, 0, 128));
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color(128, 0, 128));
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), sf::Color(128, 0, 128));
                    break;
                case 7: // Z piece
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, 0), sf::Color::Red);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, 0), sf::Color::Red);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color::Red);
                    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), sf::Color::Red);
                    break;
            }

            // Create a new piece with the chosen blocks
            Piece pieceT(pieceBlocks);
            piece = pieceT.clone();
            piece.draw(window);
            landed = false; // Reset the landed flag
        }
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
                    // Clone the piece
                    Piece pieceTemp(piece);

                    // Attempt rotation on the cloned piece
                    pieceTemp.rotateClockwise();

                    // Check for collisions and boundaries
                    if (pieceTemp.getLowestVerticalPosition() < rows - 1 &&
                        pieceTemp.getRightMostPosition() < cols &&
                        pieceTemp.getLeftMostPosition() > 1) {
                        // Apply rotation to the original piece
                        piece.rotateClockwise();
                    }
                } else if (event.key.code == sf::Keyboard::Left) {
                    // Check if the piece can move left
                    bool canMoveLeft = true;
                    for (const auto& block : piece.getBlocks()) {
                        int row = block.getPosition().y / cellSize;
                        int col = (block.getPosition().x - cellSize) / cellSize;
                        if (row >= 0 && row < rows + 1 && col >= 0 && col < cols + 2) {
                            if (grid.at(row, col) == 2) {
                                canMoveLeft = false;
                                break;
                            }
                        }
                    }

                    // Move the piece left only if it can
                    if (canMoveLeft && piece.getLeftMostPosition() != 1) {
                        piece.move(sf::Vector2f(-cellSize, 0));
                    }
                } else if (event.key.code == sf::Keyboard::Right) {
                    // Check if the piece can move right
                    bool canMoveRight = true;
                    for (const auto& block : piece.getBlocks()) {
                        int row = block.getPosition().y / cellSize;
                        int col = (block.getPosition().x + cellSize) / cellSize;
                        if (row >= 0 && row < rows + 1 && col >= 0 && col < cols + 2) {
                            if (grid.at(row, col) == 2) {
                                canMoveRight = false;
                                break;
                            }
                        }
                    }

                    // Move the piece right only if it can
                    if (canMoveRight && piece.getRightMostPosition() != cols) {
                        piece.move(sf::Vector2f(cellSize, 0));
                    }
                } else if (event.key.code == sf::Keyboard::Down) {
                    // Check if there's a piece below the current piece
                    bool canMoveDown = true;
                    for (const auto& block : piece.getBlocks()) {
                        int row = (block.getPosition().y + cellSize) / cellSize;
                        int col = block.getPosition().x / cellSize;
                        if (row >= 0 && row < rows + 1 && col >= 0 && col < cols + 2) {
                            if (grid.at(row, col) == 2) {
                                canMoveDown = false;
                                landed=true;
                                break;
                            }
                        }
                    }
                    
                    // Move the piece down only if there's no piece below it
                    if (canMoveDown && piece.getLowestVerticalPosition() != rows - 1) {
                        piece.move(sf::Vector2f(0, cellSize));
                    }
                }

                // Update landed flag if the piece has landed
                if (piece.getLowestVerticalPosition() == rows - 1) {
                    landed = true;
                }
            }

        }
        // Clear the window
        window.clear();

        // Draw the grid
        for (int i = 0; i < rows + 1; ++i) {
            for (int j = 0; j < cols + 2; ++j) {
                sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
                rect.setPosition(j * cellSize, i * cellSize);
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color::Black);
                if (j == 0 || j == cols + 1 || i == rows) {
                    grid.set(i, j, 1);
                }

                if (grid.at(i, j) == 2) {
                    rect.setFillColor(grid.getColor(i, j)); // Set color from the piece
                } else {
                    // Set color based on grid value
                    rect.setFillColor(grid.at(i, j) == 1 ? sf::Color::Green : sf::Color::White);
                }
                window.draw(rect);

                // Draw text representing the value of the cell
                sf::Text text; // Use font and size as needed
                text.setFont(font);
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Black);
                text.setString(std::to_string(grid.at(i, j)));
                text.setPosition(j * cellSize + 10, i * cellSize + 10); // Adjust position of the text
                window.draw(text);
            }
        }

        

        // Draw the piece
        piece.draw(window);

        // Display the window
        window.display();
    }

    return 0;
}