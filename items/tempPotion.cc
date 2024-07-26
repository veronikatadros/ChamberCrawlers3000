#include "../headers/items/tempPotion.h"

TempPotion::TempPotion(int value, string stat) : Item{'P', Item::TEMP_POTION}, value{value}, stat{stat}, next{nullptr} {}

TempPotion::~TempPotion() {}
