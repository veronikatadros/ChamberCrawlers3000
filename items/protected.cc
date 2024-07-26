#include "../headers/items/protected.h"
#include "../headers/enemyTypes/dragon.h"

Protected::Protected(char itemChar, ItemType itemType) : Item{itemChar, itemType}, protectedAlive{true}, protector{ new Dragon{this} } {}

Protected::~Protected() {}

void Protected::notify(Player& player) {
    protector->hostile = true;
}
