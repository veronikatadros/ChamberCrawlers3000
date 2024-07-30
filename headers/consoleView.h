#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H
#include <string>
#include "view.h"
using namespace std;

class Floor;
class Player;
class Enemy;
class Item;
class ConsoleView : public View {
        const int SPACING = 57;
    public:
        ConsoleView();
        virtual ~ConsoleView();
        void render(const Floor* floor, const int curFloor, const Player* player) override;
        void gameOver() override;
        void gameWon(Player* p) override;
        void invalidCommand() override;
        void input() override;
        void gameStart() override;
};

#endif
