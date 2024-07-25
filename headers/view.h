#include "iostream"
using namespace std;

class Floor;
class HumanPlayer;
class View {
        const int SPACING = 57;
        const string BEGCOLOR = "\\033[", ENDCOLOR = "\\033[0m";
    public:
        View();
        virtual ~View();
        string action;
        void render(const Floor& floor, const int curFloor, const HumanPlayer& player, ostream& out = cout);
};
