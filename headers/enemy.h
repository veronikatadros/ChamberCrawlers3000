#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
class Item;
class Player;

class Enemy : public Character {
        const char enemyChar;
    public:
        int spawnRate;
        bool hasAttacked;
        bool holdsCompass;

        Enemy(char enemyChar, int spawnRate, int maxHP, int atk, int def);
        virtual ~Enemy() = 0; // force this to be abstract

        char charAt() const override;
        virtual void notify(Entity* player) override;
        virtual Item* spawnLoot();
};

#endif
