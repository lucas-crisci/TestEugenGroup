#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon
{
public:
    Weapon(std::string iName, int iDamages);
    Weapon();

    std::string GetName();
    int GetDamages();

private:
    std::string _Name;
    int _Damages;
};

#endif // WEAPON_H