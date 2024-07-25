#include "../headers/items/protected.h"
#include "../headers/enemyTypes/dragon.h"

Protected::Protected(char itemChar) : Item{itemChar}, protectedAlive{true}, protector{ new Dragon{this} } {}

Protected::~Protected() {}

void Protected::notify() {
    protector->hostile = true;
}
