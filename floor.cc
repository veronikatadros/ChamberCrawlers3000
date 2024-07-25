#include <fstream>
#include <vector>
#include "cell.h"
#include "floor.h"

Floor::Floor(){
    const int rows = 25;
    const int cols = 79;
    board = std::vector<std::vector<Cell>>(rows, std::vector<Cell>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                board[i][j] = Cell(CellType::WALL); // Boundary walls
            } else if (i == 1 || i == rows - 2 || j == 1 || j == cols - 2) {
                board[i][j] = Cell(CellType::EMPTY);
            } else if (/* condition for chamber walls */) {
                board[i][j] = Cell(CellType::WALL);
            } else if (/* condition for doors */) {
                board[i][j] = Cell(CellType::DOOR);
            } else if (/* condition for passageways */) {
                board[i][j] = Cell(CellType::PASSAGE);
            } else {
                board[i][j] = Cell(CellType::GROUND);
            }
        }
    }
}


Floor::Floor(std::string filename){

    for (int row = 0; row < 25; row++){
        for (int col = 0; col < 79; col++){

        }
    }
}