#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
        char enemyChar;
    public:
        enum EnemyType {
            VAMPIRE,
            WEREWOLF,
            TROLL,
            GOBLIN,
            PHOENIX,
            MERCHANT,
            DRAGON
        };
        EnemyType enemyType;
        int spawnRate;

        Enemy(EnemyType enemyType, int maxHP, int atk, int def, Entity::EntityType entType);
        virtual ~Enemy();

        void virtual moveRandom();
        char charAt() override;
        void virtual spawnLoot();
        void virtual notify() override;
};

#endif
