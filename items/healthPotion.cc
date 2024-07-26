#include "../headers/items/healthPotion.h"

HealthPotion::HealthPotion(int value) : Item{'P', HEALTH_POTION}, value{value} {}

HealthPotion::~HealthPotion() {}
