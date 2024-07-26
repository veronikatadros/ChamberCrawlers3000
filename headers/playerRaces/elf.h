#ifndef ELF_H
#define ELF_H

#include "../player.h"

class Elf : public Player {
        void usePotion(TempPotion* p) override;
        void usePotion(HealthPotion* p) override;
    public:
        Elf();
        virtual ~Elf();
};

#endif
