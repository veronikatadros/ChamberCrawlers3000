#ifndef GOLD_H
#define GOLD_H

#include "../item.h"

class Gold : public Item {    
    public:
        float value;
        Gold(float value);
        virtual ~Gold();
};

#endif
