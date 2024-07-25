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

        void movePlayer(string dir);
        void playerAttack(string dir);
        void usePotion(string dir);
        void nextFloor();
        void reset();
    public:
        HumanPlayer& player;
        void start();

        virtual ~Game() = 0;
};



