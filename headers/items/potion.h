#ifndef POTION_H
#define POTION_H

#include "../item.h"
#include <string>
using namespace std;

class Potion : public Item {
    public:
        int value;
        const string stat;
        Potion(int value, string stat);
        virtual ~Potion();
};

#endif
