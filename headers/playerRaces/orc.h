#ifndef ORC_H
#define ORC_H

#include "../player.h"

class Orc : public Player {
        float getGoldValue(Gold* g) override;
        float getGoldValue(GoldHoard* g) override;
    public:
        Orc();
        virtual ~Orc();
};

#endif
