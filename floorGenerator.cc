#include <fstream>
#include <unordered_map>
#include "headers/randomNumberGenerator.h"
#include "headers/floor.h"
#include "headers/floorGenerator.h"
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/items/gold.h"
#include "headers/items/protected.h"
#include "headers/items/barrierSuit.h"
#include "headers/items/goldHoard.h"
#include "headers/items/permPotion.h"
#include "headers/items/tempPotion.h"
#include "headers/enemyTypes/dragon.h"
#include "headers/enemyTypes/goblin.h"
#include "headers/enemyTypes/merchant.h"
#include "headers/enemyTypes/phoenix.h"
#include "headers/enemyTypes/troll.h"
#include "headers/enemyTypes/vampire.h"
#include "headers/enemyTypes/werewolf.h"

Floor& FloorGenerator::generateFloor(const std::string& filename, Player& player) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        throw std::runtime_error("Failed to open file");
    }

    Floor* f = new Floor(); // Create the Floor object on the heap
    std::unordered_map<std::pair<int, int>, Protected*> protectedPositions;
    std::vector<std::pair<Dragon*, std::pair<int, int>>> dragonPositions;

    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < 25) {
        for (int col = 0; col < 79 && col < line.size(); ++col) {
            switch (line[col]) {
                case '@': f->board[row][col].occupant = static_cast<Entity*>(&player); 
                playerFloorLocation.push_back(std::make_pair(row, col)); break;
                case '\\': f->board[row][col].cellType = Cell::STAIRS; break;
                case '0': f->board[row][col].occupant = new PermPotion(10); break;
                case '1': f->board[row][col].occupant = new TempPotion(5, "ATK"); break;
                case '2': f->board[row][col].occupant = new TempPotion(5, "DEF"); break;
                case '3': f->board[row][col].occupant = new PermPotion(-10); break;
                case '4': f->board[row][col].occupant = new TempPotion(-5, "ATK"); break;
                case '5': f->board[row][col].occupant = new TempPotion(-5, "DEF"); break;
                case '6': f->board[row][col].occupant = new Gold(1); break;
                case '7': f->board[row][col].occupant = new Gold(2); break;
                case '8': f->board[row][col].occupant = new Gold(4); break;
                case '9': {
                    GoldHoard* gold = new GoldHoard();
                    f->board[row][col].occupant = gold;
                    protectedPositions[{row, col}] = gold;
                    break;
                }
                case 'D': {
                    Dragon* dragon = new Dragon(nullptr);
                    f->board[row][col].occupant = dragon;
                    dragonPositions.push_back({dragon, {row, col}});
                    break;
                }
                case 'B': {
                    BarrierSuit* suit = new BarrierSuit();
                    f->board[row][col].occupant = suit;
                    protectedPositions[{row, col}] = suit;
                    break;
                }
                case 'W': f->board[row][col].occupant = new Werewolf(); break;
                case 'V': f->board[row][col].occupant = new Vampire(); break;
                case 'N': f->board[row][col].occupant = new Goblin(); break;
                case 'M': f->board[row][col].occupant = new Merchant(); break;
                case 'X': f->board[row][col].occupant = new Phoenix(); break;
                case 'T': f->board[row][col].occupant = new Troll(); break;
                default:
            }
        }
        ++row;
    }
    file.close();

    // Second pass to link dragons to their protected objects
    for (auto& dragonPos : dragonPositions) {
        Dragon* dragon = dragonPos.first;
        int dr = dragonPos.second.first;
        int dc = dragonPos.second.second;
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; ++c <= 1; ++c) {
                int nr = dr + r;
                int nc = dc + c;
                if (nr >= 0 && nr < 25 && nc >= 0 && nc < 79 && !(r == 0 && c == 0)) {
                    auto it = protectedPositions.find({nr, nc});
                    if (it != protectedPositions.end()) {
                        Protected* protectedItem = it->second;
                        dragon->setHoard(protectedItem);
                        protectedItem->setProtector(dragon);
                        goto next_dragon;
                    }
                }
            }
        }
        next_dragon:;
    }

    return *f; // Return the reference to the dynamically allocated Floor object
}


Floor& FloorGenerator::generateFloor(Player& player){

}