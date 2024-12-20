#include <fstream>
#include <unordered_map>
#include <iostream>
#include "headers/randomNumberGenerator.h"
#include "headers/floorGenerator.h"
#include "headers/player.h"

#include "headers/items/gold.h"
#include "headers/items/barrierSuit.h"
#include "headers/items/goldHoard.h"
#include "headers/items/permPotion.h"
#include "headers/items/tempPotion.h"
#include "headers/items/timedPotion.h"

#include "headers/enemyTypes/dragon.h"
#include "headers/enemyTypes/goblin.h"
#include "headers/enemyTypes/merchant.h"
#include "headers/enemyTypes/phoenix.h"
#include "headers/enemyTypes/troll.h"
#include "headers/enemyTypes/vampire.h"
#include "headers/enemyTypes/werewolf.h"
using namespace std;

FloorGenerator::FloorGenerator() {
    chambers = {{{3, 3}}, 
                {{3, 39}, {5, 39}, {6, 39}, {7, 61}}, 
                {{10, 38}}, 
                {{15, 4}}, 
                {{19, 37}, {16, 65}} };
    chamberDimensions = {{{4, 26}}, 
                        {{2, 23}, {1, 31}, {1, 34}, {6, 15}}, 
                        {{3, 12}}, 
                        {{7, 21}}, 
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
        while (row < 25 && std::getline(file, line)) {
            for (int col = 0; col < 79 && static_cast<size_t>(col) < line.size(); ++col) {
                char c = line[col];
                switch (c) {
                    case '@': f->board[row][col].occupant = static_cast<Entity*>(&player); // shouldn't need cast here?
                    playerFloorLocation.push_back(make_pair(row, col)); break;
                    case '\\': f->board[row][col].cellType = Cell::STAIRS; break;
                    case '0': f->board[row][col].occupant = new PermPotion{10}; break;
                    case '1': f->board[row][col].occupant = new TempPotion{5, "ATK"}; break;
                    case '2': f->board[row][col].occupant = new TempPotion{5, "DEF"}; break;
                    case '3': f->board[row][col].occupant = new PermPotion{-10}; break;
                    case '4': f->board[row][col].occupant = new TempPotion{-5, "ATK"}; break;
                    case '5': f->board[row][col].occupant = new TempPotion{-5, "DEF"}; break;
                    case '6': f->board[row][col].occupant = new Gold{1}; break;
                    case '7': f->board[row][col].occupant = new Gold{2}; break;
                    case '8': f->board[row][col].occupant = new Gold{4}; break;
                    case '9': {
                        GoldHoard* gold = new GoldHoard{};
                        f->board[row][col].occupant = gold;
                        protectedPositions.push_back({gold, row, col});
                        break;
                    }
                    case 'D': {
                        Dragon* dragon = new Dragon{nullptr};
                        f->board[row][col].occupant = dragon;
                        dragonPositions.push_back({dragon, row, col});
                        break;
                    }
                    case 'B': {
                        BarrierSuit* suit = new BarrierSuit{};
                        f->board[row][col].occupant = suit;
                        protectedPositions.push_back({suit, row, col});
                        break;
                    }
                    case 'W': {
                        Entity* e = new Werewolf{};
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'V': {
                        Entity* e = new Vampire{};
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'N': {
                        Entity* e = new Goblin{};
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'M': {
                        Entity* e = new Merchant{};
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'X': {
                        Entity* e = new Phoenix{};
                        f->board[row][col].occupant = e;
                        f->enemyPositions.push_back({e, row, col});
                        break;
                    }
                    case 'T': {
                        Entity* e = new Troll{};
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
        

        // Second pass to link dragons to their protected objects
        for (auto& dragonPos : dragonPositions) {
            Dragon* dragon = static_cast<Dragon*>(dragonPos.entity);

            for (auto& protectedPos : protectedPositions) {
                if (abs(protectedPos.row - dragonPos.row) <= 1 && abs(protectedPos.col - protectedPos.col) <= 1) {
                    Protected* p = dynamic_cast<Protected*>(protectedPos.entity);
                    dragon->setHoard(p);
                    p->setProtector(dragon);
                    break;
                }
            }
        }
        
        floors.push_back(f); // Return the reference to the dynamically allocated Floor object
    }
    file.close();
    return floors;
}

vector<Floor*> FloorGenerator::generateFloor(Player& player) {
    vector<Floor*> floors;
    int barrierSuitFloor = RandomNumberGenerator::randomNumber(0, 4);
    for (int curFloor = 0; curFloor < 5; ++curFloor) {
        Floor* cf = new Floor();
        floors.push_back(cf);
        // 1) player position
        int playerChamber = randomChamber();
        pair<int, int> playerPos = randomFloorTile(cf, playerChamber);
        cf->board[playerPos.first][playerPos.second].occupant = &player;
        playerFloorLocation.push_back(playerPos);
        // 2) stair position
        int stairChamber = RandomNumberGenerator::randomNumber(0, 3);
        if (stairChamber >= playerChamber) stairChamber++;
        pair<int, int> stairPos = randomFloorTile(cf, stairChamber);
        cf->board[stairPos.first][stairPos.second].cellType = Cell::STAIRS;
        // 3) potions
        for (int i = 0; i < 10; ++i) {
            spawnPotion(cf);
        }
        // 4) gold
        vector<Floor::EntityPosition> protectedPositions;
        for (int i = 0; i < 10; ++i) {
            spawnGold(cf, protectedPositions);
        }
        // generate barrier suit if on correct floor
        if (curFloor == barrierSuitFloor) {
            pair<int, int> suitPos = randomFloorTile(cf, randomChamber());
            Protected* p = new BarrierSuit{};
            cf->board[suitPos.first][suitPos.second].occupant = p;
            protectedPositions.push_back({p, suitPos.first, suitPos.second});
        }
        // 5) enemies
        int enemyCount;
        // generate dragons
        for (enemyCount = 0; static_cast<size_t>(enemyCount) < protectedPositions.size(); ++enemyCount) {
            spawnDragon(cf, protectedPositions[enemyCount]);
        }

        while (enemyCount < 20) {
            spawnEnemy(cf);
            ++enemyCount;
        }

        // choose enemy with compass
        int compassEnemyIndex = RandomNumberGenerator::randomNumber(0, cf->enemyPositions.size() - 1);
        Enemy* compassEnemy = dynamic_cast<Enemy*>(cf->enemyPositions[compassEnemyIndex].entity);
        compassEnemy->holdsCompass = true;
    }
    return floors;
}

void FloorGenerator::spawnEnemy(Floor* f) {
    pair<int, int> enemyPos = randomFloorTile(f, randomChamber());
    int enemyType = RandomNumberGenerator::randomNumber(0, 17);
    Enemy* e = nullptr;
    switch (enemyType) {
        case 0:
        case 1:
        case 2:
        case 3: {
            e = new Werewolf{};
            break;
        }
        case 4:
        case 5:
        case 6: {
            e = new Vampire{};
            break;
        }
        case 7:
        case 8:
        case 9:
        case 10:
        case 11: {
            e = new Goblin{};
            break;
        }
        case 12:
        case 13: {
            e = new Troll{};
            break;
        }
        case 14:
        case 15: {
            e = new Phoenix{};
            break;
        }
        case 16:
        case 17: {
            e = new Merchant{};
            break;
        }
        default:
            break;
    }
    if (e) {
        f->board[enemyPos.first][enemyPos.second].occupant = e;
        f->enemyPositions.push_back({e, enemyPos.first, enemyPos.second});
    }
}

void FloorGenerator::spawnDragon(Floor* f, Floor::EntityPosition& procItem) {
    Protected* p = dynamic_cast<Protected*>(procItem.entity);
    // get valid cells around item (vector<Cell*>)
    vector<pair<Cell*, pair<int, int>>> validCells;
    for (int r = -1; r <= 1; ++r) {
        for (int c = -1; c <= 1; ++c) {
            int row = procItem.row + r;
            int col = procItem.col + c;
            if (row >= 0 && row < 25 && col >= 0 && col < 79) {
                Cell* temp = &(f->board[row][col]);
                if (temp->cellType == Cell::GROUND && !temp->occupant) {
                    validCells.push_back({temp, {row, col}});
                }
            }
        }
    }
    int cellNum = RandomNumberGenerator::randomNumber(0, validCells.size() - 1);
    Dragon* d = new Dragon{p};
    validCells[cellNum].first->occupant = d;
    p->protector = d;

    f->enemyPositions.push_back({d, validCells[cellNum].second.first,validCells[cellNum].second.second});
}

void FloorGenerator::spawnGold(Floor* f, vector<Floor::EntityPosition>& protectedPositions) {
    pair<int, int> goldPos = randomFloorTile(f, randomChamber());
    int goldType = RandomNumberGenerator::randomNumber(0, 7);
    switch (goldType) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            f->board[goldPos.first][goldPos.second].occupant = new Gold{1};
            break;
        case 5:
        case 6:
            f->board[goldPos.first][goldPos.second].occupant = new Gold{2};
            break;
        case 7: {
            Protected* p = new GoldHoard{};
            f->board[goldPos.first][goldPos.second].occupant = p;
            protectedPositions.push_back({p, goldPos.first, goldPos.second});
            break;
        }
        default:
            break;
    }
}

void FloorGenerator::spawnPotion(Floor* f) {
    pair<int, int> potionPos = randomFloorTile(f, randomChamber());
    int potionType = RandomNumberGenerator::randomNumber(0, 7);
    switch (potionType) {
        case 0:
            f->board[potionPos.first][potionPos.second].occupant = new PermPotion{10};
            break;
        case 1:
            f->board[potionPos.first][potionPos.second].occupant = new TempPotion{5, "ATK"};
            break;
        case 2:
            f->board[potionPos.first][potionPos.second].occupant = new TempPotion{5, "DEF"};
            break;
        case 3:
            f->board[potionPos.first][potionPos.second].occupant = new PermPotion{-10};
            break;
        case 4:
            f->board[potionPos.first][potionPos.second].occupant = new TempPotion{-5, "ATK"};
            break;
        case 5:
            f->board[potionPos.first][potionPos.second].occupant = new TempPotion{-5, "DEF"};
            break;
        case 6:
            f->board[potionPos.first][potionPos.second].occupant = new TimedPotion{4, -5};
            break;
        case 7:
            f->board[potionPos.first][potionPos.second].occupant = new TimedPotion{4, 5};
            break;
        default:
            break;
    }
}

bool FloorGenerator::emptyFloorTile(Floor* f, int row, int col) const {
    if (f->board[row][col].occupant) return false;
    if (f->board[row][col].cellType == Cell::STAIRS) return false;
    return true;
}

int FloorGenerator::randomChamber() const {
    return RandomNumberGenerator::randomNumber(0, 4);
}

pair<int, int> FloorGenerator::randomFloorTile(Floor* f, int chamber) const {
    int tile = RandomNumberGenerator::randomNumber(0, chamberFloorTiles[chamber] - 1);
    int rect;
    for (rect = 0; static_cast<size_t>(rect) < chamberDimensions[chamber].size(); ++rect) {
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
    // row, col on board

    // keep incrementing until empty pos reached
    while (!emptyFloorTile(f, row, col)) {
        // be sad
        col++;
        if (col - chambers[chamber][rect].second >= chamberDimensions[chamber][rect].second) { // at end of row
            row++;
            col = chambers[chamber][rect].second;
            if (row - chambers[chamber][rect].first >= chamberDimensions[chamber][rect].first) { // at end of rect
                rect++;
                if (static_cast<size_t>(row) >= chambers[chamber].size()) rect = 0; // at end of chamber
                row = chambers[chamber][rect].first;
                col = chambers[chamber][rect].second;
            }
        } 
    } // technically still possible for this to never find an empty tile, but would have to be *very* unlucky
    // maybe if at end of rects in chamber new chamber?

    return {row, col}; 
}
