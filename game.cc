#include<game.h>

void Game::start() {
    HumanPlayer& player = HumanPlayer::getInstance();
}

void Game::movePlayer(string dir) {
    // no,so,ea,we,ne,nw,se,sw: moves the player character one block in the appropriate cardinal direction
    if(dir == "no") {
        // floors[currentFloor].board[playerLocation.first][playerLocation.second - 1]
        if(playerLocation.second - 1 >= 0 && floors[currentFloor].board[playerLocation.first][playerLocation.second - 1] != CellType::HWALL) {
            playerLocation.second--;
            
        }
    }
    else if(dir == "so") {

    }
    else if(dir == "ea") {
        
    }
    else if(dir == "we") {
        
    }
    else if(dir == "ne") {
        
    }
    else if(dir == "nw") {
        
    }
    else if(dir == "se") {
        
    }
    else if(dir == "sw") {
        
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

