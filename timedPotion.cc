#include "headers/items/timedPotion.h"

TimedPotion::TimedPotion(int duration, int value) : Potion{value, "HP"}, duration{duration} {}

TimedPotion::~TimedPotion() {}
