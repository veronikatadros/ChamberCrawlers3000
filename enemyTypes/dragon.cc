#include "../headers/enemyTypes/dragon.h"
#include "../headers/items/compass.h"

Dragon::Dragon(Protected* hoard) : Enemy{'D', 0, 150, 20, 20}, hoard{hoard} {}

Dragon::~Dragon() {}

Item* Dragon::spawnLoot() {
    hoard->protectedAlive = false;
    if (holdsCompass) {
        return new Compass{};
    } else {
        return nullptr;
    }
}

void Dragon::notify(Player& p) {
    if (hostile) { // hoard is notified first
        Enemy::notify(p);
        hostile = false;
    }
}

void Dragon::setHoard(Protected* h){
    this->hoard = h;
}
