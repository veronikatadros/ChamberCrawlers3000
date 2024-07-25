#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"

class Character : public Entity {
    protected:
        const int maxHP;
    public:
        int hp, atk, def;
        Character(int maxHP, int atk, int def, Entity::EntityType et);
        virtual ~Character();
        bool tryKill(int damage);
};

#endif
