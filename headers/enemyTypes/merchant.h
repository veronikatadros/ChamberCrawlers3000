#ifndef MERCHANT_H
#define MERCHANT_H

#include "../enemy.h"
class Item;

class Merchant : public Enemy {
        static bool merchantsHostile;
    public:
        Merchant();
        virtual ~Merchant();
        Item* spawnLoot() override;
        void notify(Player& p) override;
        bool tryKill(int otherAtk) override;
};

#endif
