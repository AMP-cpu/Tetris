#include <SFML/Graphics.hpp>
#include <vector>

const int rows = 20;
const int cols = 10;
const int cellSize = 40;

class Block {
private:
    sf::Vector2f position;
    sf::Color color;
    int value;

public:
    Block(const sf::Vector2f& pos, const sf::Color& col, int val = 2) : position(pos), color(col), value(val) {}

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


class Piece {
private:
    std::vector<Block> blocks;

public:
    Piece(const std::vector<Block>& blocks) : blocks(blocks) {}

    const std::vector<Block>& getBlocks() const {
        return blocks;
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& block : blocks) {
            block.draw(window);
        }
    }

    Piece clone() const {
        // Create a new vector of blocks to hold the cloned blocks
        std::vector<Block> clonedBlocks;

        // Iterate over the blocks of the current piece and clone each block
        for (const auto& block : blocks) {
            // Create a new block with the same position and color as the original block
            Block clonedBlock(block.getPosition(), block.getColor());

            // Add the cloned block to the vector of cloned blocks
            clonedBlocks.push_back(clonedBlock);
        }

        // Create and return a new piece with the cloned blocks
        return Piece(clonedBlocks);
    }

    void move(const sf::Vector2f& offset) {
        for (auto& block : blocks) {
            sf::Vector2f newPos = block.getPosition() + offset;
            block.setPosition(newPos);
        }
    }

    void rotateClockwise() {
        if (blocks.empty()) {
            return;
        }

        // Find the pivot block (for example, the first block in the piece)
        const Block& pivotBlock = blocks[2];

        // Find the position of the pivot block
        sf::Vector2f pivot = pivotBlock.getPosition();

        // Rotate each block around the pivot block
        for (auto& block : blocks) {
            // Apply rotation matrix (clockwise 90 degrees)
            float newX = pivot.x + (pivot.y - block.getPosition().y);
            float newY = pivot.y - (pivot.x - block.getPosition().x);

            // Set the new position for the block
            block.setPosition(sf::Vector2f(newX, newY));
        }
    }

    void setColor(const sf::Color& color) {
        for (auto& block : blocks) {
            block.setColor(color);
        }
    }

    void setValue(int value) {
        for (auto& block : blocks) {
            block.setValue(value);
        }
    }
    
    // Function to get the position of the leftmost block
    int getLeftMostPosition() const {
        if (blocks.empty()) {
            // If there are no blocks in the piece, return an invalid position
            return -1;
        }
        
        // Initialize with the position of the first block
        sf::Vector2f leftmostPosition = blocks[0].getPosition();
        
        // Find the leftmost block
        for (const auto& block : blocks) {
            if (block.getPosition().x < leftmostPosition.x) {
                leftmostPosition = block.getPosition();
            }
        }
        
        return leftmostPosition.x/40;
    }
    int getRightMostPosition() const {
        if (blocks.empty()) {
            // If there are no blocks in the piece, return an invalid position
            return -1;
        }
        
        // Initialize with the position of the first block
        sf::Vector2f rightMostPosition = blocks[0].getPosition();
        
        // Find the rightmost block
        for (const auto& block : blocks) {
            if (block.getPosition().x > rightMostPosition.x) {
                rightMostPosition = block.getPosition();
            }
        }
        
        return rightMostPosition.x/40;
    }
    int getHighestVerticalPosition() const {
        if (blocks.empty()) {
            // If there are no blocks in the piece, return an invalid position
            return -1;
        }
        
        // Initialize with the position of the first block
        sf::Vector2f highestVerticalPosition = blocks[0].getPosition();
        
        // Find the leftmost block
        for (const auto& block : blocks) {
            if (block.getPosition().y < highestVerticalPosition.y) {
                highestVerticalPosition = block.getPosition();
            }
        }
        
        return highestVerticalPosition.y/40;
    }
    int getLowestVerticalPosition() const {
        if (blocks.empty()) {
            // If there are no blocks in the piece, return an invalid position
            return -1;
        }
        
        // Initialize with the position of the first block
        sf::Vector2f lowestVerticalPosition = blocks[0].getPosition();
        
        // Find the leftmost block
        for (const auto& block : blocks) {
            if (block.getPosition().y > lowestVerticalPosition.y) {
                lowestVerticalPosition = block.getPosition();
            }
        }
        
        return lowestVerticalPosition.y/40;
    }
    
};