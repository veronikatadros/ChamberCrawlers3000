#include <iostream>
#include <vector>

class Floor;

class GameBoard {
    public:
    virtual ~GameBoard() = 0;
    std::vector<Floor> floors;

};



