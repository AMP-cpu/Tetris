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
    

};

void Controleur::Piece_manager()
{
    Grid grid = new Grid;
    Piece piece = new Piece;
    Piece_manager manager = new Piece_manager;
}

void Controleur::~Piece_manager()
{
}



