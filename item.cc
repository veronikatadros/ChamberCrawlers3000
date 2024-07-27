#include "headers/item.h"

Item::Item(char itemChar, ItemType itemType) : Entity{EntityType::ITEM}, itemChar{itemChar}, itemType{itemType} {}

Item::~Item() {}

char Item::charAt() const {
    return itemChar;
}

void Item::notify(Entity* player) {}
