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
using namespace std;

FloorGenerator::FloorGenerator() {
    chambers = {{{2, 3}, {6, 28}}, 
                {{3, 39}, {4, 61}, {5, 39}, {3, 69}, {6, 39}, {6, 72}, {7, 61}, {12, 75}}, 
                {{10, 38}, {12, 49}}, 
                {{15, 4}, {21, 14}}, 
                {{19, 37}, {21, 64}, {16, 65}, {21, 75}} };
    chamberFloorTiles = {104, 201, 36, 77, 150};
    occupiedTiles = {0, 0, 0, 0, 0};
}

FloorGenerator::~FloorGenerator() {}

vector<Floor&> FloorGenerator::generateFloor(const string& filename, Player& player) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        throw std::runtime_error("Failed to open file");
    }
    // assume can always see the stairs
    player.hasCompass = true;
    vector<Floor&> floors;
    for (int curFloor = 0; curFloor < 5; ++curFloor) {
        Floor* f = new Floor(); // Create the Floor object on the heap
        unordered_map<pair<int, int>, Protected*> protectedPositions;
        vector<Floor::EntityPosition> dragonPositions;

        string line;
        int row = 0;
        while (std::getline(file, line) && row < 25) {
            for (int col = 0; col < 79 && col < line.size(); ++col) {
                switch (line[col]) {
                    case '@': f->board[row][col].occupant = static_cast<Entity*>(&player); // shouldn't need cast here?
                    playerFloorLocation.push_back(make_pair(row, col)); break;
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
                        dragonPositions.push_back({dragon, row, col});
                        break;
                    }
                    case 'B': {
                        BarrierSuit* suit = new BarrierSuit();
                        f->board[row][col].occupant = suit;
                        protectedPositions[{row, col}] = suit;
                        break;
                    }
                    case 'W': {
                        Entity* e = new Werewolf();
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'V': {
                        Entity* e = new Vampire();
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'N': {
                        Entity* e = new Goblin();
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'M': {
                        Entity* e = new Merchant();
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'X': {
                        Entity* e = new Phoenix();
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'T': {
                        Entity* e = new Troll();
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    default:
                }
            }
            ++row;
        }
        file.close();

        // Second pass to link dragons to their protected objects
        for (auto& dragonPos : dragonPositions) {
            Dragon* dragon = static_cast<Dragon*>(dragonPos.entity);
            int dr = dragonPos.x;
            int dc = dragonPos.y;
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
        
        floors.push_back(*f); // Return the reference to the dynamically allocated Floor object
    }
    return floors;
}

vector<Floor&> FloorGenerator::generateFloor(Player& player){
    vector<Floor&> floors;
    bool barrierSuitGenerated = false;
    for (int curFloor = 0; curFloor < 5; ++curFloor) {
        // 1 player position

        // 2 stair position
        // 3 potions
        // 4 gold (+ dragons)
        // 5 enemies
        // choose enemy to hold compass
        // barrier suit??

    }
}

int FloorGenerator::randomChamber() {
    return RandomNumberGenerator::randomNumber(0, 4);
}

pair<int, int> FloorGenerator::randomFloorTile(int chamber) {
    Entity* e = nullptr;

}
