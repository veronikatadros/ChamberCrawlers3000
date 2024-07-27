#include "headers/playerRaces/elf.h"
#include "headers/items/potion.h"

Elf::Elf() : Player{140, 30, 10, "Elf"} {}

Elf::~Elf() {}

void Elf::usePotion(Potion* p) {
    p->value = abs(p->value);
    Player::usePotion(p);
}
