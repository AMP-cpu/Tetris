#ifndef GRID_HPP
#define GRID_HPP

#include "Globals.hpp"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#pragma once



template<typename T>
class Grid
{
private:
    struct GridElement {
        T data;
        sf::Color color;
    };

    std::vector<std::vector<GridElement>> data;

public:
    // Create
    Grid(size_t rows, size_t cols, const T& defaultValue = T()) : data(rows, std::vector<GridElement>(cols, {defaultValue, sf::Color::White})) {}

    //Draw
    void draw(sf::RenderWindow& window, const sf::Font& font) {
        for (size_t row = 0; row < data.size(); ++row) {
            for (size_t col = 0; col < data[row].size(); ++col) {
                // Draw cell background
                sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1, cellSize - 1));
                cellShape.setPosition(col * cellSize, row * cellSize);
                cellShape.setFillColor(data[row][col].color);
                
                if(row==rows+1 || col==0 || col==cols+1 || row==0) {
                    set(row,col,1);
                    setColor(row,col,sf::Color::Black);
                }

                window.draw(cellShape);
                
                // // Draw cell value
                // sf::Text cellText;
                // cellText.setFont(font);
                // cellText.setCharacterSize(cellSize / 2.5); // Size of the text, adjusted to fit the cell
                // cellText.setFillColor(sf::Color::Black); // Text color

                // Convert the data to string for displaying
                std::string cellValue = std::to_string(data[row][col].data);

                // cellText.setString(cellValue);

                // // Calculate text position to center it in the cell
                // sf::FloatRect textRect = cellText.getLocalBounds();
                // cellText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
                // cellText.setPosition(sf::Vector2f(col * cellSize + cellSize / 2.0f, row * cellSize + cellSize / 2.0f));
                // window.draw(cellText);
            }
        }
    };

    bool isLineComplete(size_t row) const {
        for (const auto& element : data[row]) {
            if (element.data == 0) { // Assuming T() represents the default value
                return false; // If any element has the default value, the line is not complete
            }
        }
        return true; // All elements have non-default values, the line is complete
    }


    void eraseAndMoveLinesDown(size_t row) {
        // Start from the row to be erased and move upwards
        for (size_t i = row; i > 1; --i) {
            // Copy the values and colors from the line above
            data[i] = data[i - 1];
        }
        // Fill the first row with default values
        for (auto& element : data[0]) {
            // Set the data to some default value (e.g., 0) and color to white
            element.data = 0; // You may need to adjust this to match your default value for T
            element.color = sf::Color::White;
        }
    }

    // Value at a specific position
    T& at(size_t row, size_t col) {
        return data.at(row).at(col).data;
    }

    // Get the color of an element at a specific position
    sf::Color getColor(size_t row, size_t col) const {
        return data.at(row).at(col).color;
    }

    // Set the color of an element at a specific position
    void setColor(size_t row, size_t col, const sf::Color& newColor) {
        data.at(row).at(col).color = newColor;
    }

    // Set value at a specific position
    void set(size_t row, size_t col, const T& value) {
        data.at(row).at(col).data = value;
    }

    // Destruct
    ~Grid() {}
};

#endif