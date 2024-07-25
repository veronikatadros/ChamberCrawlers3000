#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <array>
#include "cell.h"
#include "game.h"

using namespace std;

class Floor : public Game {
    private:
    bool compassFound;
    public:
    array<array<Cell, 79>, 25> board;
    Floor();
    Floor(std::string filename);
    ~Floor();
    void printBoard() const;
};

#endif
