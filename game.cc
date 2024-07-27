#include "headers/game.h"
#include "headers/enemy.h"
#include "headers/floor.h"
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/playerRaces/human.h"
#include "headers/playerRaces/dwarf.h"
#include "headers/playerRaces/elf.h"
#include "headers/playerRaces/orc.h"
#include "headers/items/protected.h"
#include "headers/enemyTypes/merchant.h"
#include "headers/randomNumberGenerator.h"
#include <iostream>

using namespace std;

Game::Game(string cmd) : cmd{cmd}, view{new View()} {}

void Game::start() {
    cout << "Welcome to the game of CC3K!" << endl;
    cout << "Enter 'q' to quit or please enter your race: ";

    string selectRace;
    cin >> selectRace;

    if(selectRace == "h") {
        player = new Human();
    }
    else if(selectRace == "e") {
        player = new Elf();
    }
    else if(selectRace == "d") {
        player = new Dwarf();
    }
    else if(selectRace == "o") {
        player = new Orc();
    }
    else if(selectRace == "q") return;

    cout << "DONE SELECTING RACE" << endl;

    currentFloor = 0;

    cout << "DONE CURRENT FLOOR" << endl;

    // Set merchants hostiles to false
    Merchant::merchantsHostile = false;

    cout << "DONE HOSTILE" << endl;

    // Generate a floor, create an instance of the random floor generator
    generator = new FloorGenerator();
    cout << "DONE CTOR FG" << endl;
    floors = !cmd.empty() ? generator->generateFloor(cmd, *player) : generator->generateFloor(*player);
    cout << "DONE GENERATE FLOOR" << endl;

    // Player Location
    playerLocation = generator->playerFloorLocation[currentFloor];

    cout << "DONE PLAYER FLOOR LOCATION" << endl;

    view->render(floors[currentFloor], currentFloor, player);

    playTurn();
}

void Game::movePlayer(string dir) {

    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    floors[currentFloor]->board[playerLocation.first][playerLocation.second].occupant = nullptr; // set current board cell Entity to NULL
    
    if (dir == "no") { // UP
        yDir--;
    }
    else if (dir == "so") { // DOWN
        yDir++;
    }
    else if (dir == "ea") { // RIGHT
        xDir++;
    }
    else if (dir == "we") { // LEFT
        xDir--;
    }
    else if (dir == "ne") { // UP-RIGHT
        yDir--;
        xDir++;
    }
    else if (dir == "nw") { // UP-LEFT
        yDir--;
        xDir--;
    }
    else if (dir == "se") { // DOWN-RIGHT
        yDir++;
        xDir++;
    }
    else if (dir == "sw") { // DOWN-LEFT
        yDir--;
        xDir--;
    }

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor]->board.size() && xDir < floors[currentFloor]->board[playerLocation.first].size()
        && c.cellType != Cell::HWALL && c.cellType != Cell::VWALL && c.cellType != Cell::EMPTY) {
        
        if(c.occupant != nullptr) {
            if(c.occupant->eType == Entity::ITEM) {
                Item* item = static_cast<Item*>(c.occupant);
                if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS) {
                    player->pickUp(item);
                    playerLocation.first = yDir;
                    playerLocation.second = xDir;
                }
                else if(item->itemType == Item::BARRIER_SUIT || item->itemType == Item::GOLD_HOARD) {
                    Protected *p = static_cast<Protected*>(item);
                    if(!p->protectedAlive) {
                        player->pickUp(item);
                        playerLocation.first = yDir;
                        playerLocation.second = xDir;
                    }
                }
            }
        }
        else {
            if(c.cellType == Cell::STAIRS) {
                nextFloor();
                generator->playerFloorLocation[currentFloor];
            }
            else {
                playerLocation.first = yDir;
                playerLocation.second = xDir;
            }
        }
    }

    // Set current board cell entity to the player.
    Entity *p = static_cast<Entity*>(player);
    floors[currentFloor]->board[playerLocation.first][playerLocation.second].occupant = p;
    floors[currentFloor]->board[playerLocation.first][playerLocation.second].occupant->eType = Entity::PLAYER;    

    // Notify item cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int y = playerLocation.first + i;
            int x = playerLocation.second + j;
            if (y >= 0 && x >= 0 && y < floors[currentFloor]->board.size() && x < floors[currentFloor]->board[playerLocation.first].size()) {
                Cell& k = floors[currentFloor]->board[playerLocation.first + i][playerLocation.second + j];
                if(k.occupant != nullptr && k.occupant->eType == Entity::ITEM) {
                    k.occupant->notify(static_cast<Entity*>(player));
                }
            }
        }
    }

    // Notify enemy cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int y = playerLocation.first + i;
            int x = playerLocation.second + j;
            if (y >= 0 && x >= 0 && y < floors[currentFloor]->board.size() && x < floors[currentFloor]->board[playerLocation.first].size()) {
                Cell& k = floors[currentFloor]->board[playerLocation.first + i][playerLocation.second + j];
                if(k.occupant != nullptr && k.occupant->eType == Entity::ENEMY) {
                    k.occupant->notify(static_cast<Entity*>(player));
                }
            }
        }
    }
}

void Game::moveEnemies() {

    for(int k = 0; k < floors[currentFloor]->enemyPositions.size(); k++) {
        vector<Cell*> validCells;

        Floor::EntityPosition entPos = floors[currentFloor]->enemyPositions[k];
        Entity *e = entPos.entity;

        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                int y = entPos.row + i;
                int x = entPos.col + j;
                if (y >= 0 && x >= 0 && y < floors[currentFloor]->board.size() && x < floors[currentFloor]->board[playerLocation.first].size()) {
                    Cell& c = floors[currentFloor]->board[y][x];
                    if(c.cellType == Cell::GROUND && c.occupant == nullptr) validCells.push_back(&c);
                }
            }
        }

        int size = validCells.size();
        if(!validCells.empty()) {
            int ran = RandomNumberGenerator::randomNumber(0, size -1);
            Cell& curCell = floors[currentFloor]->board[entPos.row][entPos.col];
            curCell.occupant = nullptr;
            validCells[ran]->occupant = e;
        }

    }
}

void Game::playerAttack(string dir) {
    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    if (dir == "no") { // UP
        yDir--;
    }
    else if (dir == "so") { // DOWN
        yDir++;
    }
    else if (dir == "ea") { // RIGHT
        xDir++;
    }
    else if (dir == "we") { // LEFT
        xDir--;
    }
    else if (dir == "ne") { // UP-RIGHT
        yDir--;
        xDir++;
    }
    else if (dir == "nw") { // UP-LEFT
        yDir--;
        xDir--;
    }
    else if (dir == "se") { // DOWN-RIGHT
        yDir++;
        xDir++;
    }
    else if (dir == "sw") { // DOWN-LEFT
        yDir--;
        xDir--;
    }

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor]->board.size() && xDir < floors[currentFloor]->board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ENEMY) { 
            Enemy* e = static_cast<Enemy*>(c.occupant);
            bool isEnemyDead = e->tryKill(player->atk);

            if (isEnemyDead) { // if dead, replace enemy* with gold*
                Item *i = e->spawnLoot();
                // erase-remove idiom
                for (int k = 0; k < floors[currentFloor]->enemyPositions.size(); k++){
                    if (floors[currentFloor]->enemyPositions[k].entity == e){
                        std::swap(floors[currentFloor]->enemyPositions[k], floors[currentFloor]->enemyPositions[floors[currentFloor]->enemyPositions.size() - 1]);
                        floors[currentFloor]->enemyPositions.pop_back();
                    }
                }
                delete e;
                c.occupant = i;
            }
    }

}

void Game::usePotion(string dir) {
    // check it has a potion
    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    if (dir == "no") { // UP
        yDir--;
    }
    else if (dir == "so") { // DOWN
        yDir++;
    }
    else if (dir == "ea") { // RIGHT
        xDir++;
    }
    else if (dir == "we") { // LEFT
        xDir--;
    }
    else if (dir == "ne") { // UP-RIGHT
        yDir--;
        xDir++;
    }
    else if (dir == "nw") { // UP-LEFT
        yDir--;
        xDir--;
    }
    else if (dir == "se") { // DOWN-RIGHT
        yDir++;
        xDir++;
    }
    else if (dir == "sw") { // DOWN-LEFT
        yDir--;
        xDir--;
    }

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor]->board.size() && xDir < floors[currentFloor]->board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ITEM) { 
            Item* item = static_cast<Item*>(c.occupant);
            if (item->itemType == Item::POTION) {
                player->pickUp(item);
                c.occupant = nullptr;
            }
        
    }
}

void Game::nextFloor() {
    currentFloor++;
    player->removeEffects();
}

void Game::reset() {
    delete view;
    delete generator;
    delete player;

    for(auto f : floors) {
        delete f;
    }

    start();
}

void Game::playTurn() {
    while(true) {
        cout << "Input stuff :)\n";
        string input;
        cin >> input;
        if (input == "r") {
            reset();
        }
        else if (input == "q") {
            return;
        }
        else if (input == "no" || input == "so" || input == "ea" || input == "we" || input == "ne" || input == "nw" || input == "se" || input == "sw") {
            movePlayer(input);
        }
        else if (input == "u") {
            string direction;
            cin >> direction;
            usePotion(direction);
        }
        else if (input == "a") {
            string direction;
            cin >> direction;
            playerAttack(direction);
        }
        else {
            cout << "Invalid Try Again!" << endl;
        }
        view->render(floors[currentFloor], currentFloor, player);
    }
}

Game::~Game() {
    delete generator;
    delete player;
    delete view;

    for(auto f : floors) {
        delete f;
    }
}
