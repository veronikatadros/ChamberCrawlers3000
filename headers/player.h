#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "character.h"
using namespace std;

class TempPotion;
class HealthPotion;
class Item;
class Gold;
class GoldHoard;
class Potion;

class Player : public Character {
    private:
        TempPotion* potionEffect;
    protected:
        virtual int getGoldValue(Gold* g);
        virtual int getGoldValue(GoldHoard* g); // I'd like to just have GoldHoard inherit from Gold, but then deadly diamond
        virtual void usePotion(Potion* p);
    public:
        Player(int maxHP, int atk, int def, string race);
        virtual ~Player() = 0;
        
        string race;
        int gold;
        bool hasCompass;
        bool hasBarrierSuit;
        
        void pickUp(Item* i);
        virtual void removeEffects();
        
        void notify(Entity* player) override;
        char charAt() const override;
        bool tryKill(int otherAtk) override;
};

#endif
