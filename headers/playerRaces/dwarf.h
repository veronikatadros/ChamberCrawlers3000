#ifndef DWARF_H
#define DWARF_H

#include "../player.h"

class Dwarf : public Player {
        int getGoldValue(Gold& g) override;
    public:
        Dwarf();
        virtual ~Dwarf();
};

#endif