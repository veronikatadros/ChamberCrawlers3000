#include "headers/enemy.h"
#include "headers/items/gold.h"
#include "headers/items/compass.h"
#include "headers/player.h"
#include "headers/randomNumberGenerator.h"

Enemy::Enemy(char enemyChar, int spawnRate, int maxHP, int atk, int def) : 
    Character{maxHP, atk, def, EntityType::ENEMY},
    enemyChar{enemyChar}, spawnRate{spawnRate}, holdsCompass{false} {}

Enemy::~Enemy() {}

char Enemy::charAt() const {
    return enemyChar;
}

Item* Enemy::spawnLoot() { // upon enemy death (onHit returns true), return loot then game deletes Enemy
    if (holdsCompass) {
        return new Compass{};
    } else {
        return new Gold{1};
    }
}

void Enemy::notify(Entity* player) { // try to attack player
    Player* p = dynamic_cast<Player*>(player);
    hasAttacked = true;
    if (RandomNumberGenerator::randomNumber(0, 1) == 0) {
        p->tryKill(atk);
    }
    // else missed
}


