#ifndef ELF_H
#define ELF_H

#include "../player.h"

class Elf : public Player {
        void usePotion(Potion* p) override;
    public:
        Elf();
        virtual ~Elf();
};

#endif
