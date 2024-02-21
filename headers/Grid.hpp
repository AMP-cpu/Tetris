#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

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
