#include "../headers/playerRaces/elf.h"
#include "../headers/items/healthPotion.h"
#include "../headers/items/tempPotion.h"

Elf::Elf() : Player{140, 30, 10, "Elf"} {}

Elf::~Elf() {}

void Elf::usePotion(TempPotion* p) {
    p->value = abs(p->value);
    Player::usePotion(p);
}

void Elf::usePotion(HealthPotion* p) {
    p->value = abs(p->value);
    Player::usePotion(p);
}
