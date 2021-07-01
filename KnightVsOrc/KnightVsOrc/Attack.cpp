#include "Attack.h"

#include <iostream>
#include <string>

Attack::Attack(int iCibleId, int iDamages)
{
    iCibleId = _CibleId;
    iDamages = _Damages;
}

int Attack::GetCibleId()
{
    return _CibleId;
}

int Attack::GetDamages()
{
    return _Damages;
}
