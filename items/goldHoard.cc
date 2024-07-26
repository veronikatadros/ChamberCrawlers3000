#include "../headers/items/goldHoard.h"

GoldHoard::GoldHoard() : Protected{'G', GOLD_HOARD} {}

GoldHoard::~GoldHoard() {}

void GoldHoard::setProtector(Dragon* d){
    this->protector = d;
}
