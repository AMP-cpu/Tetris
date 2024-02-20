#include Piece
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
    current = next;
    delete next;
    Piece *next = new Piece;
}