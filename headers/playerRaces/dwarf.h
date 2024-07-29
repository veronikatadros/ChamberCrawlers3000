#ifndef DWARF_H
#define DWARF_H

#include "../player.h"

class Dwarf : public Player {
        float getGoldValue(Gold* g) override;
        float getGoldValue(GoldHoard* g) override;
    public:
        Dwarf();
        virtual ~Dwarf();
};

#endif
