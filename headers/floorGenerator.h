#include "floor.h"
#include<vector>

using namespace std;
class Player;

class FloorGenerator {
    private:
        vector< vector<pair<int, int>> > chambers;
        vector<int> chamberFloorTiles;
        vector<pair<int,int>> playerFloorLocation;
        int randomNumber(int low, int high);
    public:
        Floor& generateFloor();
        Floor& generateFloor(const std::string& filename, Player& player);
};

