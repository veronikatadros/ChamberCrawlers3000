#ifndef DRAGON_H
#define DRAGON_H

#include "../enemy.h"

class Item;
class Protected;

class Dragon : public Enemy {
        Protected* hoard;
    public:
        bool hostile;
        Dragon(Protected* hoard);
        virtual ~Dragon();
        Item* spawnLoot() override;
        void notify(Entity* player) override;
        void setHoard(Protected* h);
};

#endif
