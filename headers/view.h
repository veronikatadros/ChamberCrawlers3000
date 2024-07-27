#ifndef VIEW_H
#define VIEW_H

#include "iostream"
using namespace std;

class Floor;
class Player;
class Entity;
class View {
        const int SPACING = 57;
        const string BEGCOLOR = "\033[", ENDCOLOR = "\033[0m";
        string action;
    public:
        View();
        virtual ~View();
        void render(const Floor* floor, const int curFloor, const Player* player, ostream& out = cout);
        void enemyAttack(Entity* enemy, bool dead);
        void playerAttack(Entity* enemy, bool dead);
        void playerMove(string dir);
        void itemGrabbed(Entity* item);
};

#endif
