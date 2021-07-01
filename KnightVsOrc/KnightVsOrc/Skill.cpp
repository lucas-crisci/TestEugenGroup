#include "Skill.h"
#include "Status.h"

#include <iostream>
#include <string>

Skill::Skill(std::string iName, int iCooldown, int iRate, Status iEffect)
{
    _Name = iName;
    _Cooldown = iCooldown;
    _Rate = iRate;
    _Effect = iEffect;
}

Skill::Skill()
{
    _Name = "Rituel de debug";
    _Cooldown = 404;
    _Effect = Status();
}

std::string Skill::GetName()
{
    return _Name;
}

int Skill::GetCooldown()
{
    return _Cooldown;
}

int Skill::GetActualCooldown()
{
    return _ActualCooldown;
}


int Skill::GetRate()
{
    return _Rate;
}

Status Skill::GetEffect()
{
    return _Effect;
}

void Skill::DecrementActualCooldown()
{
    if(_ActualCooldown > 0)
        _ActualCooldown--;
}

void Skill::SkillUsed()
{
    _ActualCooldown = _Cooldown;
}