#ifndef MERCHANT_H
#define MERCHANT_H

#include "../enemy.h"
#include <string>

class Item;
class Potion;

class Merchant : public Enemy {
    public:
        Merchant();
        virtual ~Merchant();
        Item* spawnLoot() override;
        void notify(Entity* player) override;
        bool tryKill(int otherAtk) override;
        static bool merchantsHostile;
        Potion* sellPotion(std::string potionType);
};

#endif
