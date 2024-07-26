#include "../headers/enemyTypes/dragon.h"

Dragon::Dragon(Protected* hoard) : Enemy{'D', 0, 150, 20, 20}, hoard{hoard} {}

Dragon::~Dragon() {}

Gold* Dragon::spawnLoot() {
    hoard->protectedAlive = false;
    return nullptr;
}

void Dragon::notify() {
    if (hostile) { // hoard is notified first
        Enemy::notify();
        hostile = false;
    }
}

void Dragon::setHoard(Protected* h){
    this->hoard = h;
}
