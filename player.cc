#include "headers/player.h"
#include "headers/item.h"
#include "headers/items/potion.h"
#include "headers/items/tempPotion.h"
#include "headers/items/permPotion.h"
#include "headers/items/gold.h"
#include "headers/items/compass.h"
#include "headers/items/barrierSuit.h"
#include "headers/items/goldHoard.h"
#include <cmath>

Player::Player(int maxHP, int atk, int def, string race) : Character{maxHP, atk, def, Entity::PLAYER}, race{race}, gold{0} {}

Player::~Player() {}

void Player::pickUp(Item* i) { // these items need to be deleted in game logic
    if (i->itemType == Item::POTION) {
        usePotion(dynamic_cast<Potion*>(i));
    } else if (i->itemType == Item::GOLD) {
        Gold* g = dynamic_cast<Gold*>(i);
        gold += getGoldValue(g);
    } else if (i->itemType == Item::GOLD_HOARD) {
        GoldHoard* g = dynamic_cast<GoldHoard*>(i);
        gold += getGoldValue(g);
    } else if (i->itemType == Item::COMPASS) {
        hasCompass = true;
    } else if (i->itemType == Item::BARRIER_SUIT) {
        hasBarrierSuit = true;
    }
    delete i;
}

void Player::notify(Entity* player) {}

char Player::charAt() const {
    return '@';
}

int Player::getGoldValue(Gold* g) {
    return g->value;
}

int Player::getGoldValue(GoldHoard* g) {
    return g->value;
}

void Player::usePotion(Potion* p) {
    if (p->stat == "ATK") {
        atk += p->value;
    } else if (p->stat == "DEF") {
        def += p->value;
    } else if (p->stat == "HP") {
        hp += p->value;
        if (hp > maxHP) {
            hp = maxHP;
        }
    }
    TempPotion* tp = dynamic_cast<TempPotion*>(p);
    if (tp) {
        tp->next = potionEffect;
        potionEffect = tp;
    }
}

void Player::removeEffects() {
    // reverse each potion effect
    TempPotion* temp = potionEffect;
    while (potionEffect) {
        if (temp->stat == "ATK") {
            atk -= temp->value;
        } else if (temp->stat == "DEF") {
            def -= temp->value;
        }
        potionEffect = potionEffect->next;
        delete temp;
        temp = potionEffect;
    }
}

bool Player::tryKill(int otherAtk) {
    int damage = ceil( (100 / static_cast<float>(100 + def)) * otherAtk );
    if (hasBarrierSuit) {
        damage = ceil( damage / 2.0 );
    }
    hp -= damage;
    if (hp <= 0) {
        hp = 0;
        return true; // entity is dead, game should delete
    }
    return false;
}
