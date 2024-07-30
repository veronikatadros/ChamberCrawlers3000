#include "headers/game.h"
#include "headers/enemy.h"
#include "headers/floor.h"
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/items/potion.h"
#include "headers/playerRaces/human.h"
#include "headers/playerRaces/dwarf.h"
#include "headers/playerRaces/elf.h"
#include "headers/playerRaces/orc.h"
#include "headers/items/protected.h"
#include "headers/enemyTypes/merchant.h"
#include "headers/enemyTypes/dragon.h"
#include "headers/randomNumberGenerator.h"
#include <iostream>
#include <curses.h>

using namespace std;

Game::Game(string cmd) : player{nullptr}, view{new View()}, generator{new FloorGenerator()}, cmd{cmd} {}

void Game::start() {
    playAgain = false;

    view->gameStart();

    string selectRace;
    while(cin >> selectRace) {
        if(selectRace == "h") {
            player = new Human();
            break;
        }
        else if(selectRace == "e") {
            player = new Elf();
            break;
        }
        else if(selectRace == "d") {
            player = new Dwarf();
            break;
        }
        else if(selectRace == "o") {
            player = new Orc();
            break;
        }
        else if(selectRace == "q") return;
        else {
            view->invalidCommand();
        }
    }

    currentFloor = 0;
    // Set merchants hostiles to false
    Merchant::merchantsHostile = false;

    // Generate a floor, create an instance of the random floor generator
    floors = !cmd.empty() ? generator->generateFloor(cmd, *player) : generator->generateFloor(*player);

    // Player Location
    playerLocation = generator->playerFloorLocation[currentFloor];

    view->render(floors[currentFloor], currentFloor, player);
    playTurn();
}

void Game::movePlayer(int dir) {

    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    floors[currentFloor]->board[playerLocation.first][playerLocation.second].occupant = nullptr; // set current board cell Entity to NULL
    
    updateDir(yDir, xDir, dir);

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && static_cast<std::size_t>(yDir) < floors[currentFloor]->board.size() && static_cast<std::size_t>(xDir) < floors[currentFloor]->board[playerLocation.first].size()
        && c.cellType != Cell::HWALL && c.cellType != Cell::VWALL && c.cellType != Cell::EMPTY) {
        
        if(c.occupant != nullptr) {
            if(c.occupant->eType == Entity::ITEM) {
                Item* item = static_cast<Item*>(c.occupant);
                if(item->itemType == Item::GOLD || item->itemType == Item::COMPASS) {
                    view->itemGrabbed(item);
                    player->pickUp(item);
                    playerLocation.first = yDir;
                    playerLocation.second = xDir;
                }
                else if(item->itemType == Item::BARRIER_SUIT || item->itemType == Item::GOLD_HOARD) {
                    Protected *p = static_cast<Protected*>(item);
                    if(!p->protectedAlive) {
                        view->itemGrabbed(item);
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
                if (currentFloor < 5) playerLocation = generator->playerFloorLocation[currentFloor];
            }
            else {
                playerLocation.first = yDir;
                playerLocation.second = xDir;
            }
        }
    }

    // Set current board cell entity to the player.
    if (currentFloor < 5) {
        Entity *p = static_cast<Entity*>(player);
        floors[currentFloor]->board[playerLocation.first][playerLocation.second].occupant = p;
        floors[currentFloor]->board[playerLocation.first][playerLocation.second].occupant->eType = Entity::PLAYER;
        
        view->playerMove(dir);
    }  
}

void Game::moveEnemies() {

    for(size_t k = 0; k < floors[currentFloor]->enemyPositions.size(); k++) {
        vector<pair<int, int>> testCells;

        Floor::EntityPosition &ePos = floors[currentFloor]->enemyPositions[k];
        Entity *e = ePos.entity;

        Enemy *enem = static_cast<Enemy*>(e);
        if(enem->hasAttacked) {
            enem->hasAttacked = false;
            view->enemyAttack(enem);
            continue;
        }

        if(enem->charAt() == 'D') {
            Dragon* d = dynamic_cast<Dragon*>(enem);
            d->hostile = false;
            continue;
        }

        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                int row = ePos.row + i;
                int col = ePos.col + j;
                if (row >= 0 && col >= 0 && static_cast<std::size_t>(row) < floors[currentFloor]->board.size() && static_cast<std::size_t>(col) < floors[currentFloor]->board[playerLocation.first].size()) {
                    Cell& c = floors[currentFloor]->board[row][col];
                    pair<int, int> newCoord;
                    newCoord.first = row;
                    newCoord.second = col;
                    if(c.occupant == nullptr && c.cellType == Cell::GROUND) testCells.push_back(newCoord);
                }
            }
        }

        int size = testCells.size();
        if(size > 0) {
            int ran = RandomNumberGenerator::randomNumber(0, size - 1);
            pair<int, int> newCoord = testCells[ran];

            floors[currentFloor]->board[ePos.row][ePos.col].occupant = nullptr;
            floors[currentFloor]->board[newCoord.first][newCoord.second].occupant = e;

            ePos.row = newCoord.first;
            ePos.col = newCoord.second;
        }

    }
}


void Game::buyFromMerchant(int dir, string potionType) {
    int yDir = playerLocation.first;
    int xDir = playerLocation.second;

    updateDir(yDir, xDir, dir);

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && static_cast<std::size_t>(yDir) < floors[currentFloor]->board.size() && static_cast<std::size_t>(xDir) < floors[currentFloor]->board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ENEMY && dynamic_cast<Merchant*>(c.occupant)) { 
            Merchant* m = dynamic_cast<Merchant*>(c.occupant);
            Potion* p = m->sellPotion(potionType);
            if (!p) view->itemBought(p, player);
            else {
                view->itemBought(p, player);
                player->buyPotion(p);
            }
    }
    
}

void Game::playerAttack(int dir) {
    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    
    updateDir(yDir, xDir, dir);

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && static_cast<std::size_t>(yDir) < floors[currentFloor]->board.size() && static_cast<std::size_t>(xDir) < floors[currentFloor]->board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ENEMY) { 
            Enemy* e = static_cast<Enemy*>(c.occupant);
            bool isEnemyDead = e->tryKill(player->atk);

            view->playerAttack(e, isEnemyDead);

            if (isEnemyDead) { // if dead, replace enemy* with gold*
                Item *i = e->spawnLoot();
                // erase-remove idiom
                for (size_t k = 0; k < floors[currentFloor]->enemyPositions.size(); k++){
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

void Game::usePotion(int dir) {
    // check it has a potion
    int yDir = playerLocation.first;
    int xDir = playerLocation.second;
    
    updateDir(yDir, xDir, dir);

    Cell& c = floors[currentFloor]->board[yDir][xDir];
    if(xDir >= 0 && yDir >= 0 && static_cast<std::size_t>(yDir) < floors[currentFloor]->board.size() && static_cast<std::size_t>(xDir) < floors[currentFloor]->board[playerLocation.first].size()
        && c.occupant != nullptr && c.occupant->eType == Entity::ITEM) { 
            Item* item = static_cast<Item*>(c.occupant);
            if (item->itemType == Item::POTION) {
                view->itemGrabbed(item);
                player->pickUp(item);
                c.occupant = nullptr;
            }
        
    }
}

void Game::notifyCells() {
    // Notify item cells around the Player
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int y = playerLocation.first + i;
            int x = playerLocation.second + j;
            if (y >= 0 && x >= 0 && static_cast<std::size_t>(y) < floors[currentFloor]->board.size() && static_cast<std::size_t>(x) < floors[currentFloor]->board[playerLocation.first].size()) {
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
            if (y >= 0 && x >= 0 && static_cast<std::size_t>(y) < floors[currentFloor]->board.size() && static_cast<std::size_t>(x) < floors[currentFloor]->board[playerLocation.first].size()) {
                Cell& k = floors[currentFloor]->board[playerLocation.first + i][playerLocation.second + j];
                if(k.occupant != nullptr && k.occupant->eType == Entity::ENEMY) {
                    k.occupant->notify(static_cast<Entity*>(player));
                }
            }
        }
    }
}

void Game::updateDir(int &yDir, int &xDir, int ch) {
    switch (ch) {
        case KEY_UP:    // UP
            yDir--;
            break;
        case KEY_DOWN:  // DOWN
            yDir++;
            break;
        case KEY_LEFT:  // LEFT
            xDir--;
            break;
        case KEY_RIGHT: // RIGHT
            xDir++;
            break;
        case 'i':
            yDir--;
            xDir--;
            break;
        case 'o':
            yDir--;
            xDir++;
            break;
        case 'l':
            yDir++;
            xDir++;
            break;
        case 'k':
            yDir++;
            xDir--;
            break;
    }
}

void Game::nextFloor() {
    currentFloor++;

    if(currentFloor >= 5) {
        quitGame = true;
    }

    player->removeEffects();
    player->hasCompass = cmd.empty() ? false : true;
}

void Game::endGame() {
    quitGame = true;
    string input;
    while(cin >> input) {
        if (input == "r") {
            playAgain = true;
            return;
        }
        else if (input == "q") {
            return;
        }
        else {
             view->invalidCommand();
        }
    }
}

void Game::playTurn() {
    while(true) {
        if(player->hp <= 0 || quitGame) {
            view->gameOver();
            endGame();
            return;
        }

        view->input();

        int ch = getch(); // Get user input from curses

        if (ch == 'r') {
            playAgain = true;
            return;
        }
        else if (ch == 'q') {
            quitGame = true;
            return;
        }
        else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT || ch == 'i' || ch == 'o' || ch == 'k' || ch == 'l') {
            movePlayer(ch); // Handle movement with arrow keys
            if(quitGame) {
                view->gameWon(player);
                endGame();
                return;
            }
        }
        else if (ch == 'u') {
            int direction = getch();
            usePotion(direction);
        }
        else if (ch == 'a') {
            int direction = getch();
            playerAttack(direction);
        }
        else if (ch == 'b') {
            int direction = getch();
            string pType;
            cin >> pType;
            buyFromMerchant(direction, pType);
        }
        else {
            view->invalidActionCommand();
            view->render(floors[currentFloor], currentFloor, player);
            continue;
        }

        notifyCells();
        moveEnemies();
        player->overTimeEffects();
        view->render(floors[currentFloor], currentFloor, player);
        refresh();
    }
}

Game::~Game() {
    if(generator)
        delete generator;
    if(view)
        delete view;

    for(auto f : floors) {
        if(f)
            delete f;
    }
    if(player) {
        player->removeEffects();
        delete player;
        player = nullptr;
    }
}
