#include "headers/playerRaces/dwarf.h"
#include "headers/items/gold.h"
#include "headers/items/goldHoard.h"

Dwarf::Dwarf() : Player{100, 20, 30, "Dwarf"} {}

Dwarf::~Dwarf() {}

int Dwarf::getGoldValue(Gold* g) {
    return g->value * 2;
}

int Dwarf::getGoldValue(GoldHoard* g) {
    return g->value * 2;
}
