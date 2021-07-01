#ifndef SKILL_H
#define SKILL_H

#include "Status.h"

#include <string>

class Skill
{
public:
    Skill(std::string Name, int Cooldown, int iRate, Status iEffect);
    Skill();

    std::string GetName();
    int GetCooldown();
    int GetActualCooldown();
    int GetRate();
    Status GetEffect();
    void DecrementActualCooldown();
    void SkillUsed();

private:
    std::string _Name;
    int _Cooldown;
    int _ActualCooldown = 0;
    int _Rate;
    Status _Effect;

};

#endif // SKILL_H