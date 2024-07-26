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
            BARRIER_SUIT,
            GOLD_HOARD
        };
        ItemType itemType;
        const char itemChar;

        Item(char itemChar, ItemType itemType);
        virtual ~Item() = 0;
        char charAt() const override;
        virtual void notify(Player& player) override;
};

#endif
