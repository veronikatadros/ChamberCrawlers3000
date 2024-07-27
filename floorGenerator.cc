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
    chambers = {{{2, 3}}, 
                {{3, 39}, {5, 39}, {6, 39}, {7, 61}}, 
                {{10, 38}}, 
                {{15, 4}}, 
                {{19, 37}, {16, 65}} };
    chamberDimensions = {{{5, 26}}, 
                        {{2, 23}, {1, 31}, {1, 34}, {6, 15}}, 
                        {{3, 12}}, 
                        {{7, 11}}, 
                        {{3, 28}, {6, 11}}};
    chamberFloorTiles = {104, 201, 36, 77, 150};
    occupiedTiles = {0, 0, 0, 0, 0};
}

FloorGenerator::~FloorGenerator() {}

vector<Floor*> FloorGenerator::generateFloor(const string& filename, Player& player) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        throw std::runtime_error("Failed to open file");
    }
    // assume can always see the stairs
    player.hasCompass = true;
    vector<Floor*> floors;
    for (int curFloor = 0; curFloor < 5; ++curFloor) {
        Floor* f = new Floor(); // Create the Floor object on the heap
        //unordered_map<pair<int, int>, Protected*> protectedPositions;
        vector<Floor::EntityPosition> protectedPositions;
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
                        protectedPositions.push_back({gold, row, col});
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
                        protectedPositions.push_back({suit, row, col});
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
                        break;
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

            for (auto& protectedPos : protectedPositions) {
                if (abs(protectedPos.x - dragonPos.x) <= 1) {
                    Protected* p = dynamic_cast<Protected*>(protectedPos.entity);
                    dragon->setHoard(p);
                    p->setProtector(dragon);
                    break;
                }
            }
        }
        
        floors.push_back(f); // Return the reference to the dynamically allocated Floor object
    }
    return floors;
}

vector<Floor*> FloorGenerator::generateFloor(Player& player){
    vector<Floor*> floors;
    int barrierSuitFloor = RandomNumberGenerator::randomNumber(0, 4);
    for (int curFloor = 0; curFloor < 5; ++curFloor) {
        floors[curFloor] = new Floor();
        Floor* cf = floors[curFloor];
        // 1) player position
        int playerChamber = randomChamber();
        pair<int, int> playerPos = randomFloorTile(playerChamber);
        cf->board[playerPos.first][playerPos.second].occupant = &player;
        // 2) stair position
        int stairChamber = RandomNumberGenerator::randomNumber(0, 3);
        if (stairChamber >= playerChamber) stairChamber++;
        pair<int, int> stairPos = randomFloorTile(stairChamber);
        cf->board[stairPos.first][stairPos.second].cellType = Cell::STAIRS;
        // 3) potions
        for (int i = 0; i < 10; ++i) {
            pair<int, int> potionPos = randomFloorTile(randomChamber());
            while (!emptyFloorTile(cf, potionPos)) {
                
            }
        }
        // 4 gold (+ dragons)
        // gen barrier suit if on correct floor
        // 5 enemies
        // choose enemy to hold compass

    }
}

bool FloorGenerator::emptyFloorTile(Floor* f, pair<int, int>& tile) {
    if (f->board[tile.first][tile.second].occupant) return false;
    if (f->board[tile.first][tile.second].cellType == Cell::STAIRS) return false;
    return true;
}

int FloorGenerator::randomChamber() {
    return RandomNumberGenerator::randomNumber(0, 4);
}

pair<int, int> FloorGenerator::randomFloorTile(int chamber) {
    int tile = RandomNumberGenerator::randomNumber(0, chamberFloorTiles[chamber] - 1);
    int rect;
    for (rect = 0; rect < chamberDimensions[chamber].size(); ++rect) {
        int rectSize = chamberDimensions[chamber][rect].first * chamberDimensions[chamber][rect].second;
        if (tile <= rectSize) {
            break; // in rectangle rect of chamber
        } else {
            tile -= rectSize; // in next rect
        }
    }

    // get random row and col for specific rect, if cell is occupied cycle through rect until unoccupied space
    int row = RandomNumberGenerator::randomNumber(0, chamberDimensions[chamber][rect].first - 1);
    int col = RandomNumberGenerator::randomNumber(0, chamberDimensions[chamber][rect].second - 1);
    row += chambers[chamber][rect].first;
    col += chambers[chamber][rect].second;
    return {row, col}; // row, col on board
}
