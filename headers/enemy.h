#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "items/gold.h"
class Player;

class Enemy : public Character {
        const char enemyChar;
    public:
        int spawnRate;
        bool hasAttacked;

        Enemy(char enemyChar, int spawnRate, int maxHP, int atk, int def);
        virtual ~Enemy() = 0; // force this to be abstract

        char charAt() const override;
        virtual void notify(Player& player) override;
        virtual Gold* spawnLoot();
};

#endif
