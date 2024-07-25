#include <vector>
#include "gameBoard.h"

class Cell;

class Floor : public GameBoard {
    public:
    std::vector<std::vector<Cell>> board;
    Floor();
    Floor(std::string filename);

};
