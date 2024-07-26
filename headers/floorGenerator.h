#include "floor.h"
#include<vector>

using namespace std;
class Player;

class FloorGenerator {
    private:
        vector< vector<pair<int, int>> > chambers;
        vector<int> chamberFloorTiles;
    public:
        vector<pair<int,int>> playerFloorLocation;
        Floor& generateFloor(Player& player);
        Floor& generateFloor(const std::string& filename, Player& player);
};

