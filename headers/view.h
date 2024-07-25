#include "iostream"
using namespace std;

class Floor;
class HumanPlayer;
class View {
        const int SPACING = 57;
    public:
        View();
        virtual ~View();
        string action;
        void render(const Floor& floor, const int curFloor, const HumanPlayer& player, ostream& out = cout);
};
