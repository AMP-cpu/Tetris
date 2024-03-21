#include "../headers/Tetris.hpp"
#include "../headers/Globals.hpp"
#include <SFML/Graphics.hpp>
#include "../headers/User.hpp"
#include "../headers/Score.hpp"
#include "../headers/Menu.hpp"
#include "../headers/GameOver.hpp"
#include <iostream>
#include <ostream>
#include <sstream>

int main() {
    sf::Font font;
    if (!font.loadFromFile("font/Start.ttf")) {
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
    bool menu = true;
    int network = 0;

    while (window.isOpen()) {
        if(menu) 
            Menu(window, font, gameOver, menu, network);
        if (!gameOver && !menu)
            tetris(window, font, user, score, gameOver, menu, network);
        else if(gameOver && !menu) {            
            GameOver(window, font, user, score, gameOver, menu);
        }
    }
    


    return 0;
}