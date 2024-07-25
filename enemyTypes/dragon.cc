#include "../headers/enemyTypes/dragon.h"
#include "../headers/items/protected.h"
#include "../headers/items/gold.h"

Dragon::Dragon(Protected* hoard) : Enemy{'D', 0, 150, 20, 20}, hoard{hoard} {}

Dragon::~Dragon() {}

Gold* Dragon::spawnLoot() {
    hoard->protectedAlive = false;
    return nullptr;
}

void Dragon::notify() {
    if (hostile & !hasAttacked) { // called by hoard in case that came second as well
        Enemy::notify();
    }
}
