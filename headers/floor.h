#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <array>
#include "cell.h"
#include "game.h"

using namespace std;

class Floor : public Game {
    public:
        struct EntityPosition {
            Entity* entity;
            int x, y;
        };
        vector<EntityPosition> enemyPositions;
        array<array<Cell, 79>, 25> board;
        Floor();
        ~Floor();
};

#endif
