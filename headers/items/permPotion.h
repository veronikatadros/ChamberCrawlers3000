#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

#include "potion.h"

class PermPotion : public Potion {
    public:
        PermPotion(int value);
        virtual ~PermPotion();
};

#endif
