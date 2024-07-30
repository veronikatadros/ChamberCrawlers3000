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
        Player* player;

        pair<int, int> playerLocation;
        vector<Floor*> floors;
        int currentFloor = 0;
        View* view;
        FloorGenerator* generator;
        string cmd;
        bool quitGame = false;

        void movePlayer(int dir);
        void buyFromMerchant(int dir, string potionType);
        void moveEnemies();
        void playerAttack(int dir);
        void usePotion(int dir);
        void nextFloor();
        void playTurn();
        void notifyCells();
        void updateDir(int &yDir, int &xDir, int dir);
        void endGame();
    public:
        bool playAgain = false;
        void start();
        Game(string cmd);
        virtual ~Game();
};
#endif


