#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "./headers/Globals.hpp"

int main() {
    std::vector<std::vector<unsigned char>> matrix(COLUMNS_NUMBER, std::vector<unsigned char>(ROWS_NUMBER, 0));

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMNS_NUMBER + 8 * CELL_SIZE, CELL_SIZE * ROWS_NUMBER), "SFML Test");
    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS_NUMBER + 4 * CELL_SIZE, CELL_SIZE * ROWS_NUMBER)));

    sf::RectangleShape scoreMenu(sf::Vector2f(4 * CELL_SIZE, ROWS_NUMBER * CELL_SIZE));
    scoreMenu.setFillColor(sf::Color::Red);
    scoreMenu.setPosition(CELL_SIZE * COLUMNS_NUMBER + 1, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int cell_x = event.mouseButton.x /(CELL_SIZE+1);
                    int cell_y = event.mouseButton.y / (CELL_SIZE+1);

                    if (cell_x >= 0 && cell_x < COLUMNS_NUMBER && cell_y >= 0 && cell_y < ROWS_NUMBER) {
                        matrix[cell_x][cell_y] = 1 - matrix[cell_x][cell_y];
                    }
                    std::cout << "Position: " << static_cast<int>(cell_x)<<" "<< event.mouseButton.x << std::endl;
                }

            }
        }

        window.clear();

        for (int i = 0; i < ROWS_NUMBER; i++) {
            for (int j = 0; j < COLUMNS_NUMBER; j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                cell.setFillColor(matrix[j][i] ? sf::Color::Green : sf::Color::Blue);
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                window.draw(cell);
            }
        }

        window.draw(scoreMenu);
        window.display();
    }

    return 0;
}
