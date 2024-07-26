#ifndef ORC_H
#define ORC_H

#include "../player.h"

class Orc : public Player {
        int getGoldValue(Gold* g) override;
        int getGoldValue(GoldHoard* g) override;
    public:
        Orc();
        virtual ~Orc();
};

#endif
