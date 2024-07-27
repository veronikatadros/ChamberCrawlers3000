#include "headers/enemyTypes/merchant.h"
#include "headers/items/gold.h"
#include "headers/items/compass.h"

Merchant::Merchant() : Enemy{'M', 2, 30, 70, 5} {}

Merchant::~Merchant() {}

Item* Merchant::spawnLoot() {
    if (holdsCompass) {
        return new Compass{};
    } else {
        return new Gold{4};
    }
}

void Merchant::notify(Entity* p) {
    if (Merchant::merchantsHostile) {
        Enemy::notify(p);
    }
}

bool Merchant::tryKill(int otherAtk) {
    Merchant::merchantsHostile = true;
    return Character::tryKill(otherAtk);
}
