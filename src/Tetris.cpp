#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Grid.hpp"
#include "../headers/Blocs.hpp"
#include "../headers/Pieces.hpp"
#include "../headers/Tetris.hpp"
#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include <random> // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <chrono> // for timing
#include <algorithm>
#include <tuple>

void tetris(sf::RenderWindow& window, sf::Font font, User& user, Score& score, bool& gameOver, bool& menu, int& network) {
    // Load font for displaying cell values

    // Create a grid object
    Grid<int> grid(rows + 2, cols + 2, 0);

    bool landed = true; // Flag to indicate if the current piece has landed
    bool firstPiece = true;

    std::vector<Block> pieceBlocks;
    Piece piece(pieceBlocks);
    Piece nextPiece(pieceBlocks);

    int fallInterval = 500; // in milliseconds

    // Initialize timing variables
    auto lastTime = std::chrono::steady_clock::now();
    auto currentTime = lastTime;
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

    // Main loop
    while (window.isOpen()) {
        //Connection setup
        if (network == 1) {
            Server server = Server(1234, "localhost", 2);
            while (std::get<0>(server.Poll()) != 1)
            {
                printf("Waiting player\n");
            }
            
        }
        else if (network == 2){
            Client client = Client();
            if(client.Connect(1234,  "localhost") == 0) {
                menu=true;
                break;
            }
            client.Poll();
        }
        
        // Process events
        sf::Event event;
        if (landed || firstPiece) {
            if(!firstPiece) {
                if(piece.getHighestVerticalPosition()==1) {
                    gameOver=true;
                    break;
                }      
                int numberOfLignes = 0;
                for(int i = piece.getHighestVerticalPosition(); i<=piece.getLowestVerticalPosition(); i++) {
                    if(grid.isLineComplete(i)) {
                        grid.eraseAndMoveLinesDown(i);
                        numberOfLignes++;
                    }    
                }
                user.increasePoints(numberOfLignes);
                user.increaseLevel();
                piece = nextPiece.clone();
            }
            else {
                Piece pieceT = Piece::generateRandomPiece();
                piece = pieceT.clone();         
            }
            // Create a new piece with the chosen blocks
            Piece nextPieceT = Piece::generateRandomPiece();
            nextPiece = nextPieceT.clone();
            
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
        grid.draw(window, font);

        // Draw the pontuation
        score.draw(window,font,user.getScore(), user.getLevel());

        // Draw the piece
        piece.draw(window);
        nextPiece.drawNext(window);

        // Display the window
        window.display();

        // Increase fall velocity based on level
        fallInterval = std::max(minInterval, 500 - user.getLevel() * accelerationFactor);
    }
}
