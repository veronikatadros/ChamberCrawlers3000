#include "headers/player.h"
#include "headers/item.h"
#include "headers/items/tempPotion.h"
#include "headers/items/healthPotion.h"
#include "headers/items/gold.h"
#include "headers/items/compass.h"
#include "headers/items/barrierSuit.h"
#include "headers/items/goldHoard.h"

Player::Player(int maxHP, int atk, int def, string race) : Character{maxHP, atk, def, Entity::PLAYER}, race{race}, gold{0} {}

Player::~Player() {}

void Player::pickUp(Item* i) { // these items need to be deleted in game logic
    if (i->itemType == Item::HEALTH_POTION) {
        usePotion(dynamic_cast<HealthPotion*>(i));
    } else if (i->itemType == Item::TEMP_POTION) {
        usePotion(dynamic_cast<TempPotion*>(i));
    } else if (i->itemType == Item::GOLD) {
        Gold* g = dynamic_cast<Gold*>(i);
        gold += getGoldValue(g);
        delete g;
    } else if (i->itemType == Item::GOLD_HOARD) {
        GoldHoard* g = dynamic_cast<GoldHoard*>(i);
        gold += getGoldValue(g);
        delete g;
    } else if (i->itemType == Item::COMPASS) {
        hasCompass = true;
    } else if (i->itemType == Item::BARRIER_SUIT) {
        hasBarrierSuit = true;
    }
}

void Player::notify(Player& player) {}

char Player::charAt() const {
    return '@';
}

int Player::getGoldValue(Gold* g) {
    return g->value;
}
void Player::usePotion(TempPotion* p) {
    if (p->stat == "ATK") {
        atk += p->value;
    } else if (p->stat == "DEF") {
        def += p->value;
    }
    p->next = potionEffect;
    potionEffect = p;
}

void Player::usePotion(HealthPotion* p) {
    hp += p->value;
    if (hp > maxHP) hp = maxHP;
}

void Player::removeEffects() {
    // reverse each potion effect
    TempPotion* temp = potionEffect;
    while (potionEffect) {
        hp -= temp->value;
        potionEffect = potionEffect->next;
        temp = potionEffect;
    }
}

bool Player::tryKill(int otherAtk) {
    int damage = ceil( (100 / (100 + def)) * otherAtk );
    if (hasBarrierSuit) {
        damage = ceil( damage / 2.0 );
    }
    hp -= damage;
    if (hp <= 0) {
        return true; // entity is dead, game should delete
    }
    return false;
}