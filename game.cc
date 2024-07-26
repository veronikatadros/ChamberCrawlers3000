#include "headers/game.h"
#include "headers/enemy.h"
#include "headers/floor.h"
#include "headers/entity.h"
#include "headers/humanPlayer.h"
#include <iostream>

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

    if(dir == "no") {   // Move Up
        Cell& c = floors[currentFloor].board[playerLocation.first - 1][playerLocation.second];
        if(playerLocation.first - 1 >= 0 && c.cellType != Cell::HWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.first--;
                    }
                }
            }        
            else {
                playerLocation.first--;
            }
        }
    }
    else if(dir == "so") { // Move Down
        Cell& c = floors[currentFloor].board[playerLocation.first + 1][playerLocation.second];
        if(playerLocation.first + 1 < floors[currentFloor].board.size() && 
            c.cellType != Cell::HWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.first++;
                    }
                }
            }
            else {
                playerLocation.first++;
            }
        }

    }
    else if(dir == "ea") {  // Move Right
        Cell& c = floors[currentFloor].board[playerLocation.first][playerLocation.second + 1];
        if(playerLocation.second + 1 < floors[currentFloor].board[playerLocation.second].size() && 
            c.cellType != Cell::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.second++;
                    }
                }
            }
            else {
                playerLocation.second++;
            }
        }
        
    }
    else if(dir == "we") { // Move Left
        Cell& c = floors[currentFloor].board[playerLocation.first][playerLocation.second - 1];
        if(playerLocation.second - 1 >= 0 && c.cellType != Cell::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.second--;
                    }
                }
            }
            else {
                playerLocation.second--;
            }
        }
    }
    else if(dir == "ne") { // Move Up and Right
        Cell& c = floors[currentFloor].board[playerLocation.first - 1][playerLocation.second + 1];
        if(playerLocation.first - 1 >= 0 && playerLocation.second + 1 < floors[currentFloor].board[playerLocation.second].size() &&
             c.cellType != Cell::HWALL && c.cellType != Cell::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.first--;
                        playerLocation.second++;
                    }
                }
            }
            else {
                playerLocation.first--;
                playerLocation.second++;
            }
        }
    }
    else if(dir == "nw") {  // Move Up and Left
        Cell& c = floors[currentFloor].board[playerLocation.first - 1][playerLocation.second - 1];
        if(playerLocation.first - 1 >= 0 && playerLocation.second - 1 >= 0 &&
             c.cellType != Cell::HWALL && c.cellType != Cell::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.first--;
                        playerLocation.second--;
                    }
                }
            }
            else {
                playerLocation.first--;
                playerLocation.second--;
            }
        }
    }
    else if(dir == "se") {  // Move Down and Right
        Cell& c = floors[currentFloor].board[playerLocation.first + 1][playerLocation.second + 1];
        if(playerLocation.first + 1 < floors[currentFloor].board.size() && 
            playerLocation.second + 1 < floors[currentFloor].board[playerLocation.second].size() &&
             c.cellType != Cell::HWALL && c.cellType != Cell::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.first++;
                        playerLocation.second++;
                    }
                }
            }
            else {
                playerLocation.first++;
                playerLocation.second++;
            }
        }
    }
    else if(dir == "sw") {  // Move Down and Left
        Cell& c = floors[currentFloor].board[playerLocation.first + 1][playerLocation.second - 1];
        if(playerLocation.first + 1 < floors[currentFloor].board.size() && playerLocation.second - 1 >= 0 &&
             c.cellType != Cell::HWALL && c.cellType != Cell::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant->eType == Entity::ITEM) {
                    Item* item = static_cast<Item*>(c.occupant);
                    if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS || item->itemType == Item::BARRIER_SUIT) {
                        player.pickUp(item); // cast it to item
                        playerLocation.first++;
                        playerLocation.second--;
                    }
                }
            }
            else {
                playerLocation.first++;
                playerLocation.second--;
            }
        }
    }

    // Notify item cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; i <= 1; j++) {
            Cell& k = floors[currentFloor].board[playerLocation.first + i][playerLocation.second + j];
            if(k.occupant != nullptr && k.occupant->eType == Entity::ITEM) {
                k.occupant->notify();
            }
        }
    }
    // Notify enemy cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; i <= 1; j++) {
            Cell& k = floors[currentFloor].board[playerLocation.first + i][playerLocation.second + j];
            if(k.occupant != nullptr && k.occupant->eType == Entity::ENEMY) {
                k.occupant->notify();
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
            if (item->itemType == Item::HEALTH_POTION && item->itemType == Item::TEMP_POTION)
            player.pickUp(*item);
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
