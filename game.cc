#include"headers/game.h"
#include"headers/enemy.h"

void Game::start() {
    HumanPlayer& player = HumanPlayer::getInstance();
}

void Game::movePlayer(string dir) {

    if(dir == "no") {   // Move Up
        Cell& c = floors[currentFloor].board[playerLocation.first - 1][playerLocation.second];
        if(playerLocation.first - 1 >= 0 && c != CellType::HWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
            c != CellType::HWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
            c != CellType::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
        if(playerLocation.second - 1 >= 0 && c != CellType::VWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
             c != CellType::HWALL && c != CellType::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
             c != CellType::HWALL && c != CellType::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
             c != CellType::HWALL && c != CellType::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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
             c != CellType::HWALL && c != CellType::VWALL) {
            
            if(c.occupant != nullptr) {
                if(c.occupant.eType == EntityType::ITEM) {
                    if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                        player.pickUp(static_cast<Item*>(c.occupant)); // cast it to item
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

    // notify the cells around the player
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; i <= 1; j++) {
                Cell& k = floors[currentFloor].board[playerLocation.first + i][playerLocation.second + j];
                if(k.occupant != nullptr) {
                    k.occupant->notify();
                }
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

    Cell& c = floors[currentFloor].board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && yDir < floors[currentFloor].board.size() && xDir < floors[currentFloor].board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant.eType == EntityType::ENEMY) { 
            Enemy* e = static_cast<Enemy*>(c.occupant);
            bool isEnemyDead = e->tryKill(player.atk);

            if (isEnemyDead) { // if dead, replace enemy* with gold*
                Gold *g = e->spawnLoot();
                delete e;
                c.occupant = g;
            }
    }

}

void Game::usePotion(string dir) {

}

void Game::nextFloor() {

}

void Game::reset() {

}

