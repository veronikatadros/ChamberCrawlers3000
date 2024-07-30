#ifndef TIMED_POTION
#define TIMED_POTION

#include "potion.h"

class TimedPotion : public Potion { // takes effect over time
    public:
        int duration;
        TimedPotion(int duration, int value);
        virtual ~TimedPotion();
};

#endif
