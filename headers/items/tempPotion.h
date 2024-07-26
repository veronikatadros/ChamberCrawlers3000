#ifndef TEMP_POTION_H
#define TEMP_POTION_H

#include "potion.h"

class TempPotion : public Potion {
    public:
        TempPotion* next;
        TempPotion(int value, string stat);
        virtual ~TempPotion();
};

#endif
