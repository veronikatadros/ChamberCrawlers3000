#include "headers/enemy.h"
#include "headers/gold.h"

Enemy::Enemy(EnemyType enemyType, int maxHP, int atk, int def, Entity::EntityType entityType) : 
    Character{maxHP, atk, def, entityType},
    enemyType{enemyType}
    {
        switch (enemyType) {
            case VAMPIRE:
                enemyChar = 'V';
                spawnRate = 3;
                break;
            case WEREWOLF:
                enemyChar = 'W';
                spawnRate = 4;
                break;
            case TROLL:
                enemyChar = 'T';
                spawnRate = 2;
                break;
            case GOBLIN:
                enemyChar = 'N';
                spawnRate = 5;
                break;
            case PHOENIX:
                enemyChar = 'X';
                spawnRate = 2;
                break;
            case MERCHANT:
                enemyChar = 'M';
                spawnRate = 2;
                break;
            case DRAGON:
                enemyChar = 'D';
                spawnRate = 0; // do not spawn naturally (w/out hoard)
                break;
            default:
                // error ?
                enemyChar = '?';
                spawnRate = -1;
        }
    }

Enemy::~Enemy() {}

char Enemy::charAt() {
    return enemyChar;
}

Gold* spawnLoot() { // upon enemy death (onHit returns true), return loot then game deletes Enemy
    return new Gold{1};
}


