#ifndef PROTECTED_H
#define PROTECTED_H

#include "../item.h"
class Dragon;

class Protected : public Item { 
    public:
        Dragon* protector;
        bool protectedAlive;
        
        Protected(char itemChar, ItemType itemType);
        virtual ~Protected() = 0;
        void notify(Player& player) override;
};

#endif
