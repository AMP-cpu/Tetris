#include "Pieces.hpp"
#include "Blocs.hpp"
#include <random>
class Piece_manager
{
public:
    static Piece Change_current();

};

Piece Piece_manager::Change_current()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 7); // Distribution for 7 Tetris pieces
    int pieceNumber = dis(gen);
    switch (pieceNumber)
    {
        case 1: // Straight piece (I)
            {
                Piece pieceT = IPiece();  
                return pieceT;
            }  
            break; 
        case 2: // L piece
            {
                Piece pieceT = LPiece();  
                return pieceT;
            }
            break;
        case 3: // J piece
            {
                Piece pieceT = JPiece();  
                return pieceT;
            }
            break;
        case 4: // Square piece (O)
            {
                Piece pieceT = SquarePiece();  
                return pieceT;
            }
            break;
        case 5: // S piece
            {
                Piece pieceT = SPiece();  
                return pieceT;
            }
            break;
        case 6: // T piece
            {
                Piece pieceT = TPiece();  
                return pieceT;
            }
            break;
        case 7: // Z piece
            {
                Piece pieceT = ZPiece();  
                return pieceT;
            }
            break;
    }
}

