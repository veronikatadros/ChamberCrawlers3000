#include "headers/enemyTypes/vampire.h"
#include "headers/player.h"
#include "headers/randomNumberGenerator.h"

Vampire::Vampire() : Enemy{'V', 3, 50, 25, 25} {}

Vampire::~Vampire() {}

void Vampire::notify(Entity* player) {
    Player* p = dynamic_cast<Player*>(player);
    hasAttacked = true;
    if (RandomNumberGenerator::randomNumber(0, 1) == 0) {
        hp += 5;
        if (hp > maxHP) hp = maxHP; // heals from you
        p->tryKill(atk);
    }
    // else missed
}
