#include<floor.h>
#include<vector>

using namespace std;

class FloorGenerator {
    private:
        vector< vector<pair<int, int>> > chambers;
        vector<int> chamberFloorTiles;

        int randomNumber(int low, int high);
    public:
        Floor& generatorFloor();
};