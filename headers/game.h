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

        void movePlayer(string dir);
        void moveEnemies();
        void playerAttack(string dir);
        void usePotion(string dir);
        void nextFloor();
        void reset();
        void playTurn();
    public:
        Player* player;
        void start();

        Game(string cmd);
        virtual ~Game() = default;
};
#endif


