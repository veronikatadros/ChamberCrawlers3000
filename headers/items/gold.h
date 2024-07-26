#ifndef GOLD_H
#define GOLD_H

#include "../item.h"

class Gold : public Item {    
    public:
        int value;
        Gold(int value);
        virtual ~Gold();
};

#endif
