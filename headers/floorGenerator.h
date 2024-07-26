#include "floor.h"
#include<vector>
#include "enemy.h"

using namespace std;
class Player;

class FloorGenerator {
    private:
        vector< vector<pair<int, int>> > chambers;
        vector<int> chamberFloorTiles;
    public:
        vector<pair<int,int>> playerFloorLocation;
        vector<Floor&> generateFloor(Player& player);
        vector<Floor&> generateFloor(const std::string& filename, Player& player);
};

