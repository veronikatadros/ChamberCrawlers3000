#include "floor.h"
#include "humanPlayer.h"
using namespace std;

class View {
    public:
        string action;
        void render(const Floor& floor, const HumanPlayer& player);

};
