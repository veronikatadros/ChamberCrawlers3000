#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
        char enemyChar;
    public:
        int spawnRate;
        bool hasAttacked;

        Enemy(char enemyChar, int spawnRate, int maxHP, int atk, int def);
        virtual ~Enemy();

        char charAt() override;
        Gold* virtual spawnLoot();
        void virtual notify() override;
};

#endif
