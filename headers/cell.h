class Entity;
// Define an enum for tile types
enum class CellType {
    EMPTY,
    GROUND,
    VWALL,
    HWALL
    DOOR,
    PASSAGE,
    STAIRS
};

class Cell {
    public:
    CellType cellType;
    Entity* occupant;
    Cell(CellType c = CellType::EMPTY, Entity* e = nullptr) : cellType(c), occupant(e) {}

};