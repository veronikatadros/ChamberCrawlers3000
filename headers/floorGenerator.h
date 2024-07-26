#include "floor.h"
#include<vector>

using namespace std;
class Player;

class FloorGenerator {
    private:
        vector< vector<pair<int, int>> > chambers;
        vector<int> chamberFloorTiles;
        
        int randomNumber(int low, int high);
    public:
        vector<pair<int,int>> playerFloorLocation;
        Floor& generateFloor();
        Floor& generateFloor(const std::string& filename, Player& player);
};

