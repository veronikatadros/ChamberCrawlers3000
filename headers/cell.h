#ifndef CELL_H
#define CELL_H
class Entity;

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
        Cell(CellType c = CellType::EMPTY, Entity* e = nullptr);
        virtual ~Cell() = default;
};
#endif
