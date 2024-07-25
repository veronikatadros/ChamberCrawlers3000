#include "../headers/items/tempPotion.h"

TempPotion::TempPotion(int value, string stat) : Item{'P'}, value{value}, stat{stat}, next{nullptr} {}

TempPotion::~TempPotion() {}
