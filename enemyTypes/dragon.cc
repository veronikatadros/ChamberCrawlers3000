#include "../headers/enemyTypes/dragon.h"
#include "../headers/items/protected.h"

Dragon::Dragon(Protected* hoard) : Enemy{'D', 0, 150, 20, 20}, hoard{hoard} {}

Dragon::~Dragon() {}

Item* Dragon::spawnLoot() {
    hoard->protectedAlive = false;
    return nullptr;
}

void Dragon::notify(Entity* p) {
    if (hostile) { // hoard is notified first
        Enemy::notify(p);
        hostile = false;
    }
}

void Dragon::setHoard(Protected* h){
    this->hoard = h;
}
