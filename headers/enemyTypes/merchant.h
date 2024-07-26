#ifndef MERCHANT_H
#define MERCHANT_H

#include "../enemy.h"
class Item;

class Merchant : public Enemy {
    public:
        Merchant();
        virtual ~Merchant();
        Item* spawnLoot() override;
        void notify(Player& p) override;
        bool tryKill(int otherAtk) override;
        static bool merchantsHostile;
};

#endif
