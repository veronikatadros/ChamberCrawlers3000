#ifndef MERCHANT_H
#define MERCHANT_H

#include "../enemy.h"
class Gold;

class Merchant : public Enemy {
        static bool merchantsHostile;
    public:
        Merchant();
        virtual ~Merchant();
        Gold* spawnLoot() override;
        void notify(Player& p) override;
        bool tryKill(int otherAtk) override;
};

#endif
