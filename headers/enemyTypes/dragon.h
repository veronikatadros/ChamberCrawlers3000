#ifndef DRAGON_H
#define DRAGON_H

#include "../enemy.h"
class Gold;
class Protected;

class Dragon : public Enemy {
        Protected* hoard;
    public:
        bool hostile;
        Dragon(Protected* hoard);
        virtual ~Dragon();
        Gold* spawnLoot() override;
        void notify() override;
};

#endif
