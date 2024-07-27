#include "headers/items/tempPotion.h"

TempPotion::TempPotion(int value, string stat) : Potion{value, stat}, next{nullptr} {}

TempPotion::~TempPotion() {}
