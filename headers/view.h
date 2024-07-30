#ifndef VIEW_H
#define VIEW_H
#include <string>
using namespace std;

class Floor;
class Player;
class Enemy;
class Item;
class View {
    protected:
        const string BEGCOLOR = "\033[", ENDCOLOR = "\033[0m";
        string action;
        void getEnemyName(char enemyChar);
    public:
        View();
        virtual ~View();
        virtual void render(const Floor* floor, const int curFloor, const Player* player);
        void enemyAttack(Enemy* enemy);
        void playerAttack(Enemy* enemy, bool dead);
        void playerMove(int dir);
        void itemGrabbed(Item* item);
        void itemBought(Item* item, Player* player);
        virtual void gameOver();
        virtual void gameWon(Player* p);
        void invalidActionCommand();
        virtual void invalidCommand();
        virtual void input();
        virtual void gameStart();
};

#endif
