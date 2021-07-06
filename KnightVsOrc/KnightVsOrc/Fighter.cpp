#include "Fighter.h"

#include <iostream>
#include <string>

Fighter::Fighter(int iFighterId, std::string iName, int iHealth, Weapon iWeapon, Skill iSkill, std::vector<Status> iStatus)
{
    _FighterId = iFighterId;
    _Name = iName;
    _Health = iHealth;
    _Weapon = iWeapon;
    _Skill = iSkill;
    _Status = iStatus;
}

Fighter::Fighter()
{
    _FighterId = -1;
    _Name = "UnknowSoldier";
    _Health = 0;
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

Status Fighter::GetSkillEffect()
{
    return _Skill.GetEffect();
}

int Fighter::IsAffected(std::string StatusName)
{
    for (int idStatus = 0; idStatus < (int)_Status.size(); idStatus++)
    {
        if (_Status[idStatus].GetName() == StatusName)
            return idStatus;
    }

    return -1;
}

void Fighter::AddNewStatus(Status iNewStatus)
{
    _Status.push_back(iNewStatus);
}

void Fighter::DecrementStatusById(int iId, int iDecrementValue)
{
    if (iId < (int)_Status.size())
    {
        _Status[iId].DecrementDuration(iDecrementValue);
    }
}

void Fighter::IncrementStatusById(int iId, int iIncrementValue)
{
    if (iId < (int)_Status.size())
    {
        _Status[iId].IncrementDuration(iIncrementValue);
    }
}

void Fighter::EraseStatusIfFinished(int iId)
{
    if (_Status[iId].GetDuration() == 0)
    {
        _Status.erase(_Status.begin() + iId);
    }
}

void Fighter::UseSkill()
{
    _Skill.SkillUsed();
}

void Fighter::ReceiveDamages(int iDamages)
{
    _Health = iDamages >= _Health ? 0 : _Health - iDamages;
}

void Fighter::DecrementSkillCooldown()
{
    _Skill.DecrementActualCooldown();
}

void Fighter::DisplayFighterDatas()
{
    std::cout << "Fighter " << _FighterId + 1 << " : " << _Name << std::endl;
    std::cout << "HP : " << _Health << std::endl;
    std::cout << "Weapon : " << _Weapon.GetName() << "\t\tDamages : " << _Weapon.GetDamages() << std::endl;
    std::cout << "Skill : " << _Skill.GetName() << "\t\tCoolDown : " << _Skill.GetActualCooldown() << " / " << _Skill.GetCooldown() << std::endl;

    if (0 < _Status.size())
    {
        std::cout << "Status : ";
        for (int idStatus = 0; idStatus < (int)_Status.size(); idStatus++)
        {
            std::cout << _Status[idStatus].GetName();
            if (idStatus < (int)_Status.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Fighter::DealDamage(Fighter* iTarget)
{
    int Damages = _Weapon.GetDamages();
    iTarget->ReceiveDamages(Damages);
    std::cout << "Fighter " << _FighterId + 1 << " : " << iTarget->GetName() << " ! You receive " << Damages << " damages !" << std::endl << std::endl;
}

int Fighter::GetFighterId()
{
    return _FighterId;
}

void Fighter::LaunchSkill(std::vector<Fighter*> iFightersList)
{
    // Add Cooldown on skill
    UseSkill();

    std::string SkillName = GetSkillEffect().GetName();
    std::cout << "Fighter " << _FighterId + 1 << " : " << _Name << " is affected for " << GetSkillEffect().GetDuration();

    int IsAffectedBy = IsAffected(SkillName);
    if (IsAffectedBy >= 0)
    {
        std::cout << " more turn(s) by " << SkillName << " !" << std::endl;
        // Increment Status Duration
        IncrementStatusById(IsAffectedBy, GetSkillEffect().GetDuration());
    }
    else// Add Status
    {
        AddNewStatus(GetSkillEffect());
        std::cout << " turn(s) by " << SkillName << " !" << std::endl;
    }
}