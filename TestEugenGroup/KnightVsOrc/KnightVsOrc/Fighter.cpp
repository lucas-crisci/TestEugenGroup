#include "Fighter.h"
#include "Weapon.h"
#include "Skill.h"
#include "Status.h"

#include <iostream>
#include <string>

Fighter::Fighter(std::string iName, int iHealth, int iShield, Weapon iWeapon, Skill iSkill, std::vector<Status> iStatus)
{
    _Name = iName;
    _Health = iHealth;
    _Shield = iShield;
    _Weapon = iWeapon;
    _Skill = iSkill;
    _Status = iStatus;
}

Fighter::Fighter()
{
    _Name = "UnknowSoldier";
    _Health = 0;
    _Shield = 0;
    _Weapon = Weapon();
    _Skill = Skill();
}

std::string Fighter::GetName()
{
	return _Name;
}

int Fighter::GetHealth()
{
    return _Health;
}

int Fighter::GetShield()
{
    return _Shield;
}

Weapon Fighter::GetWeapon()
{
    return _Weapon;
}

Skill Fighter::GetSkill()
{
    return _Skill;
}

std::vector<Status> Fighter::GetAllStatus()
{
    return _Status;
}

int Fighter::IsAffected(std::string StatusName)
{
    for (int idStatus = 0; idStatus < _Status.size(); idStatus++)
    {
        if (_Status[idStatus].GetName() == StatusName)
            return idStatus;
    }

    return -1;
}

void Fighter::DecrementStatusById(int iId)
{
    if (iId < _Status.size())
    {
        _Status[iId].DecrementDuration();
    }
}

void Fighter::EraseStatusIfFinished(int iId)
{
    if (_Status[iId].GetDuration() == 0)
    {
        _Status.erase(_Status.begin() + iId);
    }
}