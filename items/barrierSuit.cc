#include "../headers/items/barrierSuit.h"

BarrierSuit::BarrierSuit() : Protected{'B', BARRIER_SUIT} {}

BarrierSuit::~BarrierSuit() {}

void BarrierSuit::setProtector(Dragon* d){
    this->protector = d;
}
