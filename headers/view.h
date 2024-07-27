#ifndef VIEW_H
#define VIEW_H


using namespace std;

class Floor;
class Player;
class Enemy;
class Item;
class View {
        const int SPACING = 57;
        const string BEGCOLOR = "\033[", ENDCOLOR = "\033[0m";
        string action;
        void getEnemyName(char enemyChar);
    public:
        View();
        virtual ~View();
        void render(const Floor* floor, const int curFloor, const Player* player);
        void enemyAttack(Enemy* enemy);
        void playerAttack(Enemy* enemy, bool dead);
        void playerMove(string dir);
        void itemGrabbed(Item* item);
        void gameOver();
        void gameWon(Player* p);
        void invalidCommand();
};

#endif
