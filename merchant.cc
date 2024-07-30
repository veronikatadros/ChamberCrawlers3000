#include "headers/enemyTypes/merchant.h"
#include "headers/items/gold.h"
#include "headers/items/compass.h"
#include "headers/items/potion.h"
#include "headers/items/tempPotion.h"
#include "headers/items/permPotion.h"
#include <string>


bool Merchant::merchantsHostile;

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

Potion* Merchant::sellPotion(std::string potionType){
    Potion* p = nullptr;
    int n = Merchant::merchantsHostile ? -1 : 1;
    if (potionType == "rh"){
        p = new PermPotion(10 * n);
    }
    else if (potionType == "ba"){
        p = new TempPotion(5 * n, "ATK");
    }
    else if (potionType == "bd"){
        p = new TempPotion(5 * n, "DEF");
    }
    return p;
}
