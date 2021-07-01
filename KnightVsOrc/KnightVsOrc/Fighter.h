#ifndef FIGHTER_H
#define FIGHTER_H

#include <string>
#include <vector>

#include "Weapon.h"
#include "Skill.h"
#include "Status.h"

class Fighter
{
public:
    Fighter(std::string iName, int iHealth, int iShield, Weapon iWeapon, Skill iSkill, std::vector<Status> iStatus = std::vector<Status>());
    Fighter();  

    std::string GetName();
    int GetHealth();
    int GetShield();
    Weapon GetWeapon();
    Skill GetSkill();
    std::vector<Status> GetAllStatus();
    Status GetSkillEffect();
    int IsAffected(std::string StatusName);
    void AddNewStatus(Status);
    void DecrementStatusById(int iId, int iDecrementValue = 1);
    void IncrementStatusById(int iId, int iIncrementValue = 1);
    void EraseStatusIfFinished(int iId);
    void UseSkill();
    void ReceiveDamages(int iDamages);

private:
    std::string _Name;
    int _Health;
    int _Shield;
    Weapon _Weapon;
    Skill _Skill;
    std::vector<Status> _Status;
};

#endif // FIGHTER_H