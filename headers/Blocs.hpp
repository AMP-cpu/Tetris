#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <SFML/Graphics.hpp>
#include "Globals.hpp"

class Block {
private:
    sf::Vector2f position;
    sf::Vector2f initialPosition; // Added member for initial position
    sf::Color color;
    int value;

public:
    Block(const sf::Vector2f& pos, const sf::Color& col, int val = 2) : position(pos), initialPosition(pos), color(col), value(val) {}

    void setPosition(const sf::Vector2f& pos) {
        position = pos;
    }

    void setColor(const sf::Color& col) {
        color = col;
    }

    void setValue(int val) {
        value = val;
    }

    const sf::Vector2f& getPosition() const {
        return position;
    }

    const sf::Vector2f& getInitialPosition() const { // Added method to return initial position
        return initialPosition;
    }

    const sf::Color& getColor() const {
        return color;
    }

    int getValue() const {
        return value;
    }

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize)); // Adjust size as needed
        shape.setPosition(position);
        shape.setFillColor(color);
        window.draw(shape);
    }
};

#endif