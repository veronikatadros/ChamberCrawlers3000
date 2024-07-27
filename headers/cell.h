#ifndef CELL_H
#define CELL_H
#include "entity.h"

class Cell {
    public:
        enum CellType {
            EMPTY,
            GROUND,
            VWALL,
            HWALL,
            DOOR,
            PASSAGE,
            STAIRS
        };
        CellType cellType;
        Entity* occupant;
        Cell(CellType c = CellType::EMPTY, Entity* e = nullptr) : cellType(c), occupant(e) {}

};
#endif
