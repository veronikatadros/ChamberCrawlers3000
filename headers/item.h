#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

class Item : public Entity {
    public:
        enum ItemType {
            HEALTH_POTION,
            TEMP_POTION,
            GOLD,
            COMPASS,
            BARRIER_SUIT
        };
        ItemType itemType;
        const char itemChar;

        Item(char itemChar);
        virtual ~Item() = 0;
        char charAt() override;
        virtual void notify() override;
};

#endif
