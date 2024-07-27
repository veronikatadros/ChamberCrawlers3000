#include "headers/playerRaces/orc.h"
#include "headers/items/gold.h"
#include "headers/items/goldHoard.h"

Orc::Orc() : Player{180, 30, 25, "Orc"} {}

Orc::~Orc() {}

int Orc::getGoldValue(Gold* g) {
    return g->value / 2;
}

int Orc::getGoldValue(GoldHoard* g) {
    return g->value / 2;
}
