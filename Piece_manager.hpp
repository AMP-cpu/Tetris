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
    void Move_piece(int x, int y);
    void Rotate_piece(int dir);

};

Piece_manager::Piece_manager()
{
    Piece *current = new Piece;
    Piece *next = new Piece;
}

Piece_manager::~Piece_manager()
{
}

void Controleur::Change_current()
{
    pi = next;
    delete next;
    Piece *next = new Piece;
}

void Controleur::Move_piece(int x, int y)
{
    piece.uptadePos(x, y);
}

void Controleur::Rotate_piece(int dir)
{
    piece.rotate(dir);
}
