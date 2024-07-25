#include <vector>
#include "game.h"

class Cell;

class Floor : public Game {
    private:
    bool compassFound;
    public:
    Cell[25][79] board;
    Floor();
    Floor(std::string filename);

};
