#ifndef OFFHANDATTACK_H
#define OFFHANDATTACK_H

#include "Spell.h"

class OffhandAttack: public Spell {
public:
    OffhandAttack(Engine* engine, Character* pchar) :
        Spell("Offhand Attack", engine, pchar, -10.0, 0) {}

protected:
private:
    int spell_effect(const int) const override;
};

#endif // OFFHANDATTACK_H
