#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "view.h"
#include "floorGenerator.h"
#include <iostream>
#include <vector>

class Floor;
class Enemy;

using namespace std;

class Game {
    private:
        pair<int, int> playerLocation;
        vector<Floor*> floors;
        int currentFloor = 0;
        View* view;
        FloorGenerator* generator;
        string cmd;
        bool quitGame = false;

        void movePlayer(string dir);
        void buyFromMerchant(string dir, string potionType);
        void moveEnemies();
        void playerAttack(string dir);
        void usePotion(string dir);
        void nextFloor();
        void reset();
        void playTurn();
        void notifyCells();
        void updateDir(int &yDir, int &xDir, string dir);
        void endGame();
    public:
        Player* player;
        bool playAgain = false;
        void start();

        Game(string cmd);
        virtual ~Game();
};
#endif


