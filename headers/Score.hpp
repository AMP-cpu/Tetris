#ifndef PLAYER_SCORE_HPP
#define PLAYER_SCORE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

class Score {
private:
    int score;

public:
    // Constructor
    Score(int initialScore = 0) : score(initialScore) {}

    // Getter for player score
    int getScore() const {
        return score;
    }

    // Getter for player score
    void reset() {
        score=0;
    }

    // Method to update player's score
    void updateScore(int newScore) {
        score = newScore;
    }

    void draw(sf::RenderWindow& window, const sf::Font& font, int score, int level) {
        
                sf::RectangleShape cellShape(sf::Vector2f(8*cellSize, 16*cellSize));
                cellShape.setPosition(14 * cellSize, 1 * cellSize);
                cellShape.setFillColor(sf::Color::Black);
                

                window.draw(cellShape);

                // Draw "SCORE" text
                sf::Text scoreText;
                scoreText.setFont(font);
                scoreText.setCharacterSize(cellSize); // Adjust size as needed
                scoreText.setFillColor(sf::Color::White);
                scoreText.setString("SCORE");
                scoreText.setPosition(14 * cellSize + (8 * cellSize - scoreText.getLocalBounds().width) / 2, 3 * cellSize - scoreText.getLocalBounds().height);
                window.draw(scoreText);
                
                // Draw cell value
                sf::Text cellText;
                cellText.setFont(font);
                cellText.setCharacterSize(cellSize * 1.5); // Size of the text, adjusted to fit the cell
                cellText.setFillColor(sf::Color::White); // Text color

                // Convert the data to string for displaying
                std::string cellValue = std::to_string(score);

                cellText.setString(cellValue);

                // Calculate text position to center it in the cell
                sf::FloatRect textRect = cellText.getLocalBounds();
                cellText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
                cellText.setPosition(sf::Vector2f(18 * cellSize, 4 * cellSize));
                window.draw(cellText);

                // Draw "LEVEL" text
                sf::Text levelText;
                levelText.setFont(font);
                levelText.setCharacterSize(cellSize); // Adjust size as needed
                levelText.setFillColor(sf::Color::White);
                levelText.setString("LEVEL");
                levelText.setPosition(14 * cellSize + (8 * cellSize - levelText.getLocalBounds().width) / 2, 6 * cellSize - levelText.getLocalBounds().height);
                window.draw(levelText);
                
                // Draw level value
                sf::Text levelValue;
                levelValue.setFont(font);
                levelValue.setCharacterSize(cellSize * 1.5); // Size of the text, adjusted to fit the cell
                levelValue.setFillColor(sf::Color::White); // Text color

                levelValue.setString(std::to_string(level));

                // Calculate text position to center it in the cell
                sf::FloatRect levelRect = levelValue.getLocalBounds();
                levelValue.setOrigin(levelRect.left + levelRect.width/2.0f, levelRect.top + levelRect.height/2.0f);
                levelValue.setPosition(sf::Vector2f(18 * cellSize, 8 * cellSize));
                window.draw(levelValue);
        
    };
};

#endif // PLAYER_SCORE_HPP
