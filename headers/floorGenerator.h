#ifndef FLOOR_GEN_H
#define FLOOR_GEN_H

#include<vector>
#include "floor.h"
#include "enemy.h"

using namespace std;
class Player;

class FloorGenerator {
    private:
        vector< vector<pair<int, int>> > chambers;
        vector<int> chamberFloorTiles;
        vector< vector<pair<int, int>> > chamberDimensions;
        vector<int> occupiedTiles;
        int randomChamber();
        pair<int, int> randomFloorTile(int chamber); // random floor tile
        bool emptyFloorTile(Floor* f, pair<int, int>& tile); // returns whether tile is empty
    public:
        FloorGenerator();
        virtual ~FloorGenerator();
        vector<pair<int,int>> playerFloorLocation;
        vector<Floor*> generateFloor(Player& player);
        vector<Floor*> generateFloor(const std::string& filename, Player& player);
};

#endif
