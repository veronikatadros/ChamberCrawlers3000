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
        bool hasAttacked;

        Enemy(EnemyType enemyType, int maxHP, int atk, int def, Entity::EntityType entType);
        virtual ~Enemy();

        char charAt() override;
        Gold* virtual spawnLoot();
        void virtual notify() override;
};

#endif
