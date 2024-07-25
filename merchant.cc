#include "merchant.h"

Merchant::Merchant() : Enemy{'M', 2, 30, 70, 5} {}

Merchant::~Merchant() {}

Gold* Merchant::spawnLoot() { return nullptr; }

void Merchant::notify() {
    if (Merchant::merchantsHostile) {
        Enemy::notify();
    }
}

bool Merchant::tryKill(int otherAtk) {
    Merchant::merchantsHostile = true;
    Character::tryKill(otherAtk);
}
