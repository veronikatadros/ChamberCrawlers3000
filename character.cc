#include "headers/character.h"
#include <math.h>
#include <iostream>
using namespace std;

Character::Character(int maxHp, int atk, int def, Entity::EntityType entityType) : 
                                        Entity{entityType}, maxHP{maxHp}, hp{maxHp}, atk{atk}, def{def} {}

Character::~Character() {}

bool Character::tryKill(int otherAtk) {
    hp -= ceil( (100 / static_cast<float>(100 + def)) * otherAtk );
    if (hp <= 0) {
        hp = 0;
        return true; // entity is dead, game should delete
    }
    return false;
}
