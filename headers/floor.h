#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <array>
#include "cell.h"

using namespace std;

class Floor {
    public:
        struct EntityPosition {
            Entity* entity;
            int row, col;
        };
        vector<EntityPosition> enemyPositions;
        array<array<Cell, 79>, 25> board;
        Floor();
        virtual ~Floor();
};

#endif
