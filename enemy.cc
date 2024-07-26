#include "headers/enemy.h"
#include "headers/items/gold.h"
#include "headers/player.h"

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
    // generate random number??
    player.tryKill(atk); // this needs to only be half accurate
}


