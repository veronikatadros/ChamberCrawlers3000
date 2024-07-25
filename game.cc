#include<game.h>

void Game::start() {
    HumanPlayer& player = HumanPlayer::getInstance();
}

void Game::movePlayer(string dir) {
    
    if(dir == "no") {   // Move Up
        Cell& c = floors[currentFloor].board[playerLocation.first - 1][playerLocation.second];
        if(playerLocation.first - 1 >= 0 && c != CellType::HWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.first--;
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
            c != CellType::HWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.first++;
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
            c != CellType::VWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.second++;
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
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.second--;
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
             c != CellType::HWALL && c != CellType::VWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.first--;
                    playerLocation.second++;
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
             c != CellType::HWALL && c != CellType::VWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.first--;
                    playerLocation.second--;
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
             c != CellType::HWALL && c != CellType::VWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.first++;
                    playerLocation.second++;
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
             c != CellType::HWALL && c != CellType::VWALL && c.occupant.eType != EntityType::ENEMY) {
            
            if(c.occupant.eType == EntityType::ITEM) {
                if(c.occupant.type == ItemType::GOLD || c.occupant.type == ItemType::COMPASS || c.occupant.type == ItemType::BARRIER_SUIT) {
                    player.pickUp(static_cast<Item> (c.occupant)); // cast it to item
                    playerLocation.first++;
                    playerLocation.second--;
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

}

void Game::usePotion(string dir) {

}

void Game::nextFloor() {

}

void Game::reset() {

}

