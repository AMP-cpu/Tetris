#include Grid
#include Piece
#include Piece_manager
class Controleur
{
private:
    Piece piece;
    Grid grid;
    Piece_manager manager;
public:
    Controleur();
    ~Controleur();
    void Change_current();

};

Controleur::Piece_manager()
{
    Grid grid = new Grid;
    Piece piece = new Piece;
    Piece_manager manager = new Piece_manager;
}

Controleur::~Piece_manager()
{
}

void Controleur::Change_current()
{
    current = next;
    delete next;
    Piece *next = new Piece;
}