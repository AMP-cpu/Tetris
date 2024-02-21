#include <SFML/Graphics.hpp>
#include "../headers/Grid.hpp"
#include "../headers/Blocs.hpp" 

int main() {
    // Define grid parameters
    

    // Load font for displaying cell values
    sf::Font font;
    if (!font.loadFromFile("font/Arial.ttf")) {
        // Failed to load font, handle the error
        std::cerr << "Failed to load font" << std::endl;
    }

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode((cols+2) * cellSize, (rows+1) * cellSize), "SFML Grid");
    window.setVerticalSyncEnabled(true); // Enable VSync

    // Create a grid object
    Grid<int> grid(rows+1, cols+2, 0);

    // Create a vector to hold blocks
    std::vector<Block> blocks;

    // Create a piece
    std::vector<Block> pieceBlocks;
    // Add blocks to the piece
    // Example:
    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 3, 0), sf::Color::Red);
    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, 0), sf::Color::Red);
    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 5, 0), sf::Color::Red);
    pieceBlocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), sf::Color::Red);
    Piece piece(pieceBlocks);

    

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle keyboard input
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left && piece.getLeftMostPosition()!=1) {
                    piece.move(sf::Vector2f(-cellSize, 0));
                }
                else if (event.key.code == sf::Keyboard::Right && piece.getRightMostPosition()!= cols) {
                    piece.move(sf::Vector2f(cellSize, 0));
                }
                else if (event.key.code == sf::Keyboard::Down && piece.getLowestVerticalPosition()!= rows-1) {
                    piece.move(sf::Vector2f(0, cellSize));
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    Piece pieceTemp = piece.clone();
                    pieceTemp.rotateClockwise();
                    std::cout<<pieceTemp.getLeftMostPosition()<<std::endl;
                    if(pieceTemp.getLowestVerticalPosition() < rows-1 && pieceTemp.getRightMostPosition() < cols && pieceTemp.getLeftMostPosition() > 1)
                        piece.rotateClockwise();
                }
                
            }
        }

        

        // Clear the window
        window.clear();

        // Draw the grid
        for (int i = 0; i < rows+1; ++i) {
            for (int j = 0; j < cols+2; ++j) {
                sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
                rect.setPosition(j * cellSize, i * cellSize);
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color::Black);
                if(j==0 || j==cols+1 || i==rows) {
                    grid.set(i,j,1);
                }
                    
                rect.setFillColor(grid.at(i, j) == 1 ? sf::Color::Green : sf::Color::White);
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

        // Draw the blocks
        for (const auto& block : blocks) {
            block.draw(window);
        }

        // Draw the piece
        piece.draw(window);

        // Display the window
        window.display();
    }

    return 0;
}
