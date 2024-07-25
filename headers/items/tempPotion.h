#ifndef TEMP_POTION_H
#define TEMP_POTION_H

#include "../item.h"
#include <string>
using namespace std;

class TempPotion : public Item {
    public:
        const int value;
        const string stat;
        TempPotion* next;
        TempPotion(int value, string stat);
        virtual ~TempPotion();
};

#endif
