#ifndef ATTACK_H
#define ATTACK_H

#include "Status.h"

#include <string>

class Attack
{
public:
    Attack(int iCibleId, int iDamages);
    //Attack();

    int GetCibleId();
    int GetDamages();

private:
    int _CibleId;
    int _Damages;
};

#endif // ATTACK_H