#include "iostream"
using namespace std;

class Floor;
class HumanPlayer;
class View {
    public:
        View();
        virtual ~View();
        string action;
        void render(const Floor& floor, const HumanPlayer& player, ostream& out = cout);
};
