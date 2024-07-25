#include "headers/item.h"

Item::Item(char itemChar) : Entity{EntityType::ITEM}, itemChar{itemChar} {}

Item::~Item() {}

char Item::charAt() {
    return itemChar;
}

void Item::notify() {}
