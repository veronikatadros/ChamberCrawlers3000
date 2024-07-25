#ifndef GOLD_H
#define GOLD_H

#include "../item.h"

class Gold : public Item {
        const int value;
    public:
        Gold(int value);
        ~Gold();
};

#endif
