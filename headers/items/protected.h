#ifndef PROTECTED_H
#define PROTECTED_H

#include "../item.h"
class Dragon;

class Protected : public Item {
        Dragon* protector;
    public:
        bool protectedAlive;
        
        Protected(char itemChar);
        virtual ~Protected() = 0;
        void notify() override;
};

#endif
