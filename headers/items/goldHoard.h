#ifndef GOLD_HOARD_H
#define GOLD_HOARD_H

#include "protected.h"

class GoldHoard : public Protected {
        const int value = 6;
    public:
        GoldHoard();
        virtual ~GoldHoard();
};

#endif
