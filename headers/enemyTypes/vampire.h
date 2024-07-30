#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "../enemy.h"

class Vampire : public Enemy {
    public:
        Vampire();
        virtual ~Vampire();
        void notify(Entity* player) override;
};

#endif
