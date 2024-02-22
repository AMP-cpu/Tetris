#include Piece
#include <random>
class Piece_manager
{
private:
    Piece current;
    Piece next;
public:
    Piece_manager();
    ~Piece_manager();
    void Change_current();

};

Piece_manager::Piece_manager()
{
    Piece *current = new Piece;
    Piece *next = new Piece;
}

Piece_manager::~Piece_manager()
{
}

void Piece_manager::Change_current()
{
    delete current;
    current = next;
    delete next;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 7); // Distribution for 7 Tetris pieces
    int pieceNumber = dis(gen);

    Piece *next = new Piece(pieceNumber);
}
