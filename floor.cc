#include <fstream>
#include "headers/cell.h"
#include "headers/floor.h"

Floor::Floor(): compassFound(false){
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 79; ++j) {
            if (j == 0 || j == 78) {
                board[i][j] = Cell(CellType::VWALL); // Vertical Boundary walls
            } 
            else if (i == 0 || i == 24){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if ((i == 3 || i == 4) && (j >= 39 && j <= 61)){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (i == 5 && (j >=39 && j <= 69)){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (i == 6 && (j >=39 && j <= 72)){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (i == 1 || i == 23){
                board[i][j] = Cell(CellType::EMPTY);
            }
            else if (j == 1 || j == 77){
                board[i][j] = Cell(CellType::EMPTY);
            }
            else if (i >= 2 && i <= 7 && j == 2){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 2 && ((j >= 3 && j <= 28) || (j >=39 && j <= 61))){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (i >= 3 && i <= 6 && j >= 3 && j <= 28){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (i == 7 && ((j >= 3 && j != 13 && j <= 28) || (j >= 39 && j <= 59 && j != 43))){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 13 && i == 7){
                board[i][j] =  Cell(CellType::DOOR);
            }
            else if ((i == 7 || i == 9) &&  j == 43){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if ((j == 29 || j == 38) && (i == 2 || i == 3 || i == 5 || i == 6 || i == 7)){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 4 && (j == 29 || j == 38)){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if (i == 4 && (j >= 30 && j <= 37)){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i == 4 && j >= 63 && j <= 69){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 62 && (i == 2 || i == 3 || i == 4)){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (j == 70 && (i == 4 || i == 5)){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 5 && (j == 71 || j == 72)){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 73 && (i == 6 || i == 5)){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 6 && (j == 74 || j == 75)){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 60 && (i >= 7 && i <= 13 && i != 11)){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (j == 60 && i == 11){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if (j == 76 && i >= 6 && i <= 13){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (j >= 61 && j <= 75 && i >= 7 && i <= 12){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (j >= 61 && j <= 75 && j != 69 && i == 13){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 69 && i == 13){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if (j == 33 && i >= 5 && i <= 7){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (j == 13 && i >= 8 && i <= 13){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (j == 31 && i >= 8 && i <= 19){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (j == 54 && i >= 11 && i <= 16){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i == 11 && j >= 14 && j <= 30){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i == 8 && j >= 32 && j <= 43){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (j == 43 && i >= 14 && i <= 17){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i == 16 && j >= 32 && j <= 53){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i == 20 && j >= 26 && j <= 35){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i >= 9 && i <= 13 && (j == 37 || j == 50) ){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if ((i == 9 || i == 13) && (j >= 38 && j <= 49 && j != 43) ){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 43 && (i == 9 || i == 13 || i == 18)){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if ((j >= 38 && j <= 49) && (i == 10 || i == 11 || i == 12)){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (i == 11 && j >= 55 && j <= 59){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (i == 14 && j == 69){
                board[i][j] = Cell(CellType::PASSAGE);
            }
            else if (j == 3 && i >= 14 && i <= 22){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 14 && j >= 4 && j <= 24 && j != 13){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (i == 14 && j == 13){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if (i == 22 && j >= 4 && j <= 24){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (j == 25 && i >= 14 && i <= 22 && i != 20){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if ((j == 25 || j == 36) && i == 20){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if (j >= 4 && j <= 24 && i >= 14 && i <= 21){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (j == 36 && i >= 18 && i <= 22 && i != 20){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 18 && j >= 37 && j <= 63 && j != 43){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (i == 22 && j >= 37 && j <= 75){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (i >= 15 && i <= 18 && j == 64){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i == 15 && j >= 65 && j <= 75 && j != 69){
                board[i][j] = Cell(CellType::HWALL);
            }
            else if (i == 15 && j == 69){
                board[i][j] = Cell(CellType::DOOR);
            }
            else if (j == 76 && i >= 15 && i <= 22){
                board[i][j] = Cell(CellType::VWALL);
            }
            else if (i >= 19 && i <= 21 && j >= 37 && j <= 64){
                board[i][j] = Cell(CellType::GROUND);
            }
            else if (i >= 16 && i <= 21 && j >= 65 && j <= 75){
                board[i][j] = Cell(CellType::GROUND);
            }
            else{
                board[i][j] = Cell(CellType::EMPTY);
            }
        }
    }

}


void Floor::printBoard() const {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            switch (cell.cellType) {
                case CellType::EMPTY: std::cout << ' '; break;
                case CellType::GROUND: std::cout << '.'; break;
                case CellType::VWALL: std::cout << '|'; break;
                case CellType::HWALL: std::cout << '-'; break;
                case CellType::DOOR: std::cout << '+'; break;
                case CellType::PASSAGE: std::cout << '#'; break;
                case CellType::STAIRS: std::cout << '/'; break;
            }
        }
        std::cout << '\n';
    }
}

Floor::~Floor(){}