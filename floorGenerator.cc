#include <fstream>
#include "headers/floor.h"
#include "headers/floorGenerator.h"
#include "headers/entity.h"
#include "headers/humanPlayer.h"
#include "headers/items/gold.h"
#include "headers/items/potion.h"
#include "headers/enemyTypes/dragon.h"
#include "headers/enemyTypes/goblin.h"
#include "headers/enemyTypes/merchant.h"
#include "headers/enemyTypes/phoenix.h"
#include "headers/enemyTypes/troll.h"
#include "headers/enemyTypes/vampire.h"
#include "headers/enemyTypes/werewolf.h"

Floor& FloorGenerator::generateFloor(string& filename){
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    Floor* f = new Floor();

    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < 25) {
        for (int col = 0; col < 79 && col < line.size(); ++col) {
            switch (line[col]) {
                case '@': f->board[row][col].occupant = new ;
                default: board[row][col] = Cell(CellType::EMPTY); break;
            }
        }
        ++row;
    }
    file.close();
}