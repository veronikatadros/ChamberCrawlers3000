#include "headers/enemy.h"
#include "headers/items/gold.h"
#include "headers/player.h"
#include "headers/randomNumberGenerator.h"

Enemy::Enemy(char enemyChar, int spawnRate, int maxHP, int atk, int def) : 
    Character{maxHP, atk, def, EntityType::ENEMY},
    enemyChar{enemyChar}, spawnRate{spawnRate} {}

Enemy::~Enemy() {}

char Enemy::charAt() const {
    return enemyChar;
}

Gold* Enemy::spawnLoot() { // upon enemy death (onHit returns true), return loot then game deletes Enemy
    return new Gold{1};
}

void Enemy::notify(Player& player) { // try to attack player
    hasAttacked = true;
    if (RandomNumberGenerator::randomNumber(0, 1) == 0) {
        player.tryKill(atk);
    }
    // else missed
}


