#include "Blocs.hpp"
#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


class Piece {
protected:
    std::vector<Block> blocks;

public:
    Piece(const std::vector<Block>& blocks) : blocks(blocks) {}
    Piece() {}

    ~Piece() {}

    const std::vector<Block>& getBlocks() const {
        return blocks;
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& block : blocks) {
            block.draw(window);
        }
    }

    void drawNext(sf::RenderWindow& window) const {
        // Define the position to draw the next piece
        sf::Vector2f offset(13.5*cellSize, 11*cellSize); // Adjust as needed

        for (const auto& block : blocks) {
            // Set the block's position relative to the starting position
            sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize)); // Adjust size as needed
            shape.setPosition(block.getPosition() + offset);
            shape.setFillColor(block.getColor());
            window.draw(shape);
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

    Piece cloneInitial() const {
        // Create a new vector of blocks to hold the cloned blocks
        std::vector<Block> clonedBlocks;

        // Iterate over the blocks of the current piece and clone each block
        for (const auto& block : blocks) {
            // Create a new block with the same initial position and color as the original block
            sf::Vector2f initialPosition = block.getInitialPosition();
            sf::Color color = block.getColor();
            Block clonedBlock(initialPosition, color);

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

    void moveRight(Grid<int>& grid) {
        if (!(grid.at(getLowestVerticalPosition(), getRightMostPosition()+1) == 2) && !(getLowestVerticalPosition() == rows - 1) && !(getRightMostPosition()==cols)) {
            move(sf::Vector2f(cellSize, 0));
        }
    }

    void moveLeft(Grid<int>& grid) {
        if (!(grid.at(getLowestVerticalPosition(), getLeftMostPosition()-1) == 2) && !(getLowestVerticalPosition() == rows - 1) && !(getLeftMostPosition()==1)) {
            move(sf::Vector2f(-cellSize, 0));
        }
    }

    void moveDown(Grid<int>& grid, bool* landed) {
        // Check if there's a piece below the current piece
        bool canMoveDown = true;
        for (const auto& block : getBlocks()) {
            int row = (block.getPosition().y + cellSize) / cellSize;
            int col = block.getPosition().x / cellSize;
            if (row > 0 && row <= rows + 1) {
                if (grid.at(row, col) == 2 || row == rows+1 || getLowestVerticalPosition() == 20) {
                    for (const auto& block : getBlocks()) {
                        int row = block.getPosition().y / cellSize;
                        int col = block.getPosition().x / cellSize;
                        grid.set(row, col, 2); // Set the corresponding grid cell to 1 to indicate the block is occupied
                        grid.setColor(row, col, block.getColor());
                    }
                    canMoveDown = false;
                    *landed=true;
                    break;
                }
            }
        }
                        
        // Move the piece down only if there's no piece below it
        if (canMoveDown) {
            move(sf::Vector2f(0, cellSize));
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

    void rotateClockwiseIfPossible(Grid<int>& grid) {
        // Check if the current piece is the O piece (piece number 4)
        if (blocks[0].getPosition()+sf::Vector2f(cellSize, 0) == blocks[1].getPosition()  && blocks[2].getPosition()+sf::Vector2f(cellSize, 0) == blocks[3].getPosition() && blocks[0].getPosition()+sf::Vector2f(0, cellSize)==blocks[2].getPosition()) {
            // If it's the O piece, return without rotating
            return;
        }

        // Clone the piece
        Piece pieceTemp(clone());

        // Attempt rotation on the cloned piece
        pieceTemp.rotateClockwise();

        // Check if any of the cells the piece would occupy after rotation are already occupied
        for (const auto& block : pieceTemp.getBlocks()) {
            int row = block.getPosition().y / cellSize;
            int col = block.getPosition().x / cellSize;
            if (row >= 0 && row < rows+1 && col > 0 && col < cols+1) {
                if (grid.at(row, col) == 2 || grid.at(row, col)==1) {
                    // If any cell is occupied, return without rotating the original piece
                    return;
                }
            } else {
                // If any cell is out of bounds, return without rotating the original piece
                return;
            }
        }

        // If no cell is occupied and all cells are within bounds, apply rotation to the original piece
        rotateClockwise();
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
            if (block.getPosition().y >= lowestVerticalPosition.y) {
                lowestVerticalPosition = block.getPosition();
            }
        }
        
        return lowestVerticalPosition.y/40;
    }

    std::string Serialize() const {
        std::ostringstream oss;
        oss << blocks.size() << " ";
        for (const auto& element : blocks) {
             oss << element.getPosition().x << " " << element.getPosition().y << " " << element.getInitialPosition().x << " " << element.getInitialPosition().y << " " << element.getColor().toInteger() << " ";
        }
        oss << ",";
        return oss.str();
    }

    // Deserialization of the Grid object
    void Deserialize(const std::string& serializedData) {
        std::istringstream iss(serializedData);
        int nblocks;
        iss >> nblocks;
        blocks.clear();
        for (;nblocks > 0; nblocks --) {
            int x, y, ix, iy, color;
            iss >> x;
            iss >> y;
            iss >> ix;
            iss >> iy;
            iss >> color;
            Block clonedBlock(sf::Vector2f(ix, iy), sf::Color(color));
            clonedBlock.setPosition(sf::Vector2f(x,y));
            blocks.push_back(clonedBlock);
        }
    }


    static Piece generateRandomPiece();
};

class IPiece : public Piece {
    public:

    IPiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        for (int i = 0; i < 4; ++i) { 
           blocks.emplace_back(sf::Vector2f(cellSize * (i + 3), cellSize), color);
        }
    }
};

class LPiece : public Piece {
    public:

    LPiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        blocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize), color);
        for (int i = 0; i < 3; ++i) {
            blocks.emplace_back(sf::Vector2f(cellSize * (i + 3), cellSize * 2), color);
        }
    }


};

class JPiece : public Piece {
    public:

    JPiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        blocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), color);
        for (int i = 0; i < 3; ++i) {
            // sf::Color color = colors[colorDis(gen)];
            blocks.emplace_back(sf::Vector2f(cellSize * (i + 3), cellSize * 2), color);
        }
    }


};

class SquarePiece : public Piece {
    public:

    SquarePiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize * 2), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize * 2), color);
    }


};

class SPiece : public Piece {
    public:

    SPiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize * 2), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize * 2), color);
    }


};


class TPiece : public Piece {
    public:

    TPiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize * 2), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize * 2), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize * 2), color);
    }


};

class ZPiece : public Piece {
    public:

    ZPiece(sf::Color color) {
        // Create a vector to hold blocks for the chosen piece
        blocks.emplace_back(sf::Vector2f(cellSize * 3, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 4, cellSize * 2), color);
        blocks.emplace_back(sf::Vector2f(cellSize * 5, cellSize * 2), color);
    }


};

Piece Piece::generateRandomPiece() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 7); // Distribution for 7 Tetris pieces
        int pieceNumber = dis(gen);

        // Create a vector to hold blocks for the chosen piece
        std::vector<Block> pieceBlocks;

        Piece pieceT;

        // Define a vector of possible colors
        std::vector<sf::Color> colors = {
            sf::Color::Cyan,
            sf::Color::Blue,
            sf::Color(255, 165, 0), // Orange
            sf::Color::Yellow,
            sf::Color::Green,
            sf::Color(128, 0, 128), // Purple
            sf::Color::Red
        };

        // Randomly select a color for each block within the piece
        std::uniform_int_distribution<> colorDis(0, colors.size() - 1);
        sf::Color color = colors[colorDis(gen)];

        switch (pieceNumber)
        {

            case 1: // Straight piece (I)
                {
                    pieceT = IPiece(color);  
                }  
                break; 
            case 2: // L piece
                {
                    pieceT = LPiece(color);  

                }
                break;
            case 3: // J piece
                {
                    pieceT = JPiece(color);  

                }
                break;
            case 4: // Square piece (O)
                {
                    pieceT = SquarePiece(color);  

                }
                break;
            case 5: // S piece
                {
                    pieceT = SPiece(color);  

                }
                break;
            case 6: // T piece
                {
                    pieceT = TPiece(color);  

                }
                break;
            case 7: // Z piece
                {
                    pieceT = ZPiece(color);  

                }
                break;
        }

        return pieceT;
    };

    
    