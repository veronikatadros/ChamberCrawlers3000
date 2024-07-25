#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

#include "../item.h"

class HealthPotion : public Item {
    public:
        const int value;
        HealthPotion(int value);
        virtual ~HealthPotion();
};

#endif
