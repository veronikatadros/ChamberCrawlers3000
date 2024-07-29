#include "headers/playerRaces/dwarf.h"
#include "headers/items/gold.h"
#include "headers/items/goldHoard.h"

Dwarf::Dwarf() : Player{100, 20, 30, "Dwarf"} {}

Dwarf::~Dwarf() {}

float Dwarf::getGoldValue(Gold* g) {
    return g->value * 2.0;
}

float Dwarf::getGoldValue(GoldHoard* g) {
    return g->value * 2.0;
}
