#include "headers/character.h"

Character::Character(int maxHp, int atk, int def, Entity::EntityType et) : 
                                        Entity{et}, maxHP{maxHP}, atk{atk}, def{def} 
{
    hp = maxHP;
}

Character::~Character() {}

bool Character::tryKill(int damage) {
    hp -= damage;
    if (hp <= 0) {
        return true; // entity is dead, game should delete
    }
    return false;
}
