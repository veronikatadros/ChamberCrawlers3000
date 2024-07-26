#include "../headers/items/potion.h"

Potion::Potion(int value, string stat) : Item{'P', Item::POTION}, value{value}, stat{stat} {}

Potion::~Potion() {}
