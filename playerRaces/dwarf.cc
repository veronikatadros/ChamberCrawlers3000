#include "../headers/playerRaces/dwarf.h"
#include "../headers/items/gold.h"
#include "../headers/items/goldHoard.h"

Dwarf::Dwarf() : Player{140, 30, 10, "Dwarf"} {}

Dwarf::~Dwarf() {}

int Dwarf::getGoldValue(Gold* g) {
    return g->value * 2;
}

int Dwarf::getGoldValue(GoldHoard* g) {
    return g->value * 2;
}
