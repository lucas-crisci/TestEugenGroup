#ifndef FIGHTER_H
#define FIGHTER_H

#include "Weapon.h"
#include "Skill.h"
#include "Status.h"

#include <string>
#include <vector>
#include <iostream>

#define SKILLSTUNNAME "Stun";
#define SKILLCHARGENAME "Charge";

class Fighter
{
public:
    Fighter(int iFighterId, std::string iName, int iHealths, Weapon iWeapon, Skill iSkill, std::vector<Status> iStatus = std::vector<Status>());
    Fighter();  

    int GetFighterId();
    std::string GetName();
    int GetHealth();
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
    void DecrementSkillCooldown();
    
    virtual void ReceiveDamages(int iDamages);
    virtual void DisplayFighterDatas();
    virtual void DealDamage(Fighter* iTarget);
    virtual void LaunchSkill(std::vector<Fighter*> iFightersList);

protected:
    int _FighterId;
    std::string _Name;
    int _Health;
    Weapon _Weapon;
    Skill _Skill;
    std::vector<Status> _Status;
};

#endif // FIGHTER_H