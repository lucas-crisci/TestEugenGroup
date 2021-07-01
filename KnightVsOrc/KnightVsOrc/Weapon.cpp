#include "Weapon.h"

#include <iostream>
#include <string>

Weapon::Weapon(std::string iName, int iDamages)
{
    _Name = iName;
    _Damages = iDamages;
}

Weapon::Weapon()
{
    _Name = "Truelle magique";
    _Damages = 178;
}

std::string Weapon::GetName()
{
    return _Name;
}


int Weapon::GetDamages()
{
    return _Damages;
}
