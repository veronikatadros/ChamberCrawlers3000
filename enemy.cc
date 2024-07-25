#include "headers/enemy.h"
#include "headers/items/gold.h"
#include "headers/humanPlayer.h"

Enemy::Enemy(char enemyChar, int spawnRate, int maxHP, int atk, int def) : 
    Character{maxHP, atk, def, EntityType::ENEMY},
    enemyChar{enemyChar}, spawnRate{spawnRate} {}

Enemy::~Enemy() {}

char Enemy::charAt() {
    return enemyChar;
}

Gold* Enemy::spawnLoot() { // upon enemy death (onHit returns true), return loot then game deletes Enemy
    return new Gold{1};
}

void Enemy::notify() { // try to attack player
    hasAttacked = true;
    // generate random number??
    HumanPlayer& player = HumanPlayer::getInstance(); // using singleton pattern
    player.tryKill(atk); // this needs to only be half accurate
}


