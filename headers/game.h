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
        bool useCurses = false;

        void movePlayer(int dir, string direction = "");
        void buyFromMerchant(string potionType, int dir, string direction = "");
        void moveEnemies();
        void playerAttack(int dir, string direction = "");
        void usePotion(int dir, string direction = "");
        void nextFloor();
        void playTurn();
        void notifyCells();
        void updateDir(int &yDir, int &xDir, int ch, string direction = "");
        void endGame();
    public:
        bool playAgain = false;
        void start();
        Game(string cmd, bool useCurses);
        virtual ~Game();
};
#endif


