#include "humanPlayer.h"
#include "view.h"
#include "floorGenerator.h"
#include <iostream>
#include <vector>

class Floor;

using namespace std;

class Game {
    private:
        pair<int, int> playerLocation;
        vector<Floor&> floors;
        int currentFloor = 0;
        View view;
        FloorGenerator generator;
        vector<Enemy*> enemies;

        void movePlayer(string dir);
        void moveEnemies();
        void playerAttack(string dir);
        void usePotion(string dir);
        void nextFloor();
        void reset();
        void playTurn();
    public:
        HumanPlayer& player;
        void start();

        Game();
        ~Game();
};



