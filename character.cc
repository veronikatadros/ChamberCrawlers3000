#include "headers/character.h"
#include <math.h>
using namespace std;

Character::Character(int maxHp, int atk, int def, Entity::EntityType entityType) : 
                                        Entity{entityType}, maxHP{maxHP}, atk{atk}, def{def} 
{
    hp = maxHP;
}

Character::~Character() {}

bool Character::tryKill(int otherAtk) {
    hp -= ceil( (100 / (100 + def)) * otherAtk );
    if (hp <= 0) {
        return true; // entity is dead, game should delete
    }
    return false;
}
