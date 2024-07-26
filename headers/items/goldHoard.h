#ifndef GOLD_HOARD_H
#define GOLD_HOARD_H

#include "protected.h"
class Dragon;

class GoldHoard : public Protected {
    public:
        int value = 6;
        GoldHoard();
        virtual ~GoldHoard();
        void setProtector(Dragon* d);
};

#endif
