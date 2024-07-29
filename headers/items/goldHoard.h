#ifndef GOLD_HOARD_H
#define GOLD_HOARD_H

#include "protected.h"

class GoldHoard : public Protected {
    public:
        float value = 6.0;
        GoldHoard();
        virtual ~GoldHoard();
};

#endif
