#include "headers/items/protected.h"
#include "headers/enemyTypes/dragon.h"

Protected::Protected(char itemChar, ItemType itemType) : Item{itemChar, itemType}, protectedAlive{true}, protector{nullptr} {}

Protected::~Protected() {}

void Protected::notify(Entity* player) {
    protector->hostile = true;
}

void Protected::setProtector(Dragon* d){
    protector = d;
}
