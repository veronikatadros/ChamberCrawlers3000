#include "headers/game.h"
#include "headers/enemy.h"
#include "headers/floor.h"
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/items/protected.h"
#include "iostream"

using namespace std;

// Game::Game() {

// }

void Game::start() {
    // set merchant hostiles to false

    string selectRace;
    cin >> selectRace;

    if(selectRace == "h") {
        // player = new HumanPlayer
    }
    else if(selectRace == "e") {
        // player = new Elf
    }
    else if(selectRace == "d") {
        // player = new Dwarf
    }
    else if(selectRace == "o") {
        // player = new Orc
    }
}

void Game::movePlayer(string dir) {

    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    floors[currentFloor].board[playerLocation.first][playerLocation.second].occupant = nullptr; // set current board cell Entity to NULL
    
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

    Cell& c = floors[currentFloor].board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor].board.size() && xDir < floors[currentFloor].board[playerLocation.first].size()
        && c.cellType != Cell::HWALL && c.cellType != Cell::VWALL) {
        
        if(c.occupant != nullptr) {
            if(c.occupant->eType == Entity::ITEM) {
                Item* item = static_cast<Item*>(c.occupant);
                if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS) {
                    player.pickUp(item);
                    playerLocation.first = yDir;
                    playerLocation.second = xDir;
                }
                else if(item->itemType == Item::BARRIER_SUIT || item->itemType == Item::GOLD_HOARD) {
                    Protected *p = static_cast<Protected*>(item);
                    if(!p->protectedAlive) {
                        player.pickUp(item);
                        playerLocation.first = yDir;
                        playerLocation.second = xDir;
                    }
                }
            }
        }
        else {
            if(c.cellType == Cell::STAIRS) {
                nextFloor();
                generator.playerFloorLocation[currentFloor];
            }
            else {
                playerLocation.first = yDir;
                playerLocation.second = xDir;
            }
        }
    }

    // Set current board cell entity to the player.
    Entity *p = static_cast<Entity*>(&player);
    floors[currentFloor].board[playerLocation.first][playerLocation.second].occupant = p;
    floors[currentFloor].board[playerLocation.first][playerLocation.second].occupant->eType = Entity::PLAYER;    

    // Notify item cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; i <= 1; j++) {
            Cell& k = floors[currentFloor].board[playerLocation.first + i][playerLocation.second + j];
            if(k.occupant != nullptr && k.occupant->eType == Entity::ITEM) {
                k.occupant->notify(player);
            }
        }
    }
    
    // Notify enemy cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; i <= 1; j++) {
            Cell& k = floors[currentFloor].board[playerLocation.first + i][playerLocation.second + j];
            if(k.occupant != nullptr && k.occupant->eType == Entity::ENEMY) {
                k.occupant->notify(player);
            }
        }
    }
}

void Game::moveEnemies() {

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

    Cell& c = floors[currentFloor].board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor].board.size() && xDir < floors[currentFloor].board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ENEMY) { 
            Enemy* e = static_cast<Enemy*>(c.occupant);
            bool isEnemyDead = e->tryKill(player.atk);

            if (isEnemyDead) { // if dead, replace enemy* with gold*
                Gold *g = e->spawnLoot();
                // erase-remove idiom
                enemies.erase(remove(enemies.begin(), enemies.end(), e), enemies.end());
                delete e;
                c.occupant = g;
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

    Cell& c = floors[currentFloor].board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor].board.size() && xDir < floors[currentFloor].board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ITEM) { 
            Item* item = static_cast<Item*>(c.occupant);
            if (item->itemType == Item::POTION)
            player.pickUp(item);
    }
}

void Game::nextFloor() {
    currentFloor++;
    player.removeEffects();
}

void Game::reset() {
    // delete a bunch of shit
    // call Game::start()
}

void Game::playTurn() {
    while(true) {
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
        view.render(floors[currentFloor], currentFloor, player);
    }
}
