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
        int randomChamber() const;
        pair<int, int> randomFloorTile(Floor* f, int chamber) const; // random floor tile
        bool emptyFloorTile(Floor* f, int row, int col) const; // returns whether tile is empty
        void spawnPotion(Floor* f);
        void spawnGold(Floor* f, vector<Floor::EntityPosition>& protectedPositions);
        void spawnDragon(Floor* f, Floor::EntityPosition& procItem);
        void spawnEnemy(Floor* f);
    public:
        FloorGenerator();
        virtual ~FloorGenerator();
        vector<pair<int,int>> playerFloorLocation;
        vector<Floor*> generateFloor(Player& player);
        vector<Floor*> generateFloor(const std::string& filename, Player& player);
};

#endif
