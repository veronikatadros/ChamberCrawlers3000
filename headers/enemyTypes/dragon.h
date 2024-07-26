#ifndef DRAGON_H
#define DRAGON_H

#include "../enemy.h"
#include "../headers/items/goldHoard.h"

class Gold;
class GoldHoard;
class Protected;

class Dragon : public Enemy {
        Protected* hoard;
    public:
        bool hostile;
        Dragon(Protected* hoard);
        virtual ~Dragon();
        Gold* spawnLoot() override;
        void notify(Player& p) override;
        void setHoard(Protected* h);
};

#endif
