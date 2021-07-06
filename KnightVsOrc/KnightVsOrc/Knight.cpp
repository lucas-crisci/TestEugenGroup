#include "Knight.h"

Knight::Knight(int iFighterId, std::string iName, int iHealth, Weapon iWeapon, int iShield, std::vector<Status> iStatus) :
	Fighter(iFighterId, iName, iHealth, iWeapon, Skill(), iStatus)
{
	_Shield = iShield;

    std::string ChargeName = SKILLCHARGENAME;
    Status SkillStatus = Status(ChargeName, 1);
    _Skill = Skill(ChargeName, 3, 60, SkillStatus);
}

int Knight::GetShield()
{
    return _Shield;
}

void Knight::ReceiveDamages(int iDamages)
{
    if (_Shield > 0)
    {
        int RemainingDamage = iDamages >= _Shield ? (iDamages - _Shield) : 0;
        _Shield = iDamages >= _Shield ? 0 : _Shield - iDamages;
        Fighter::ReceiveDamages(RemainingDamage);
    }
    else
    {
        Fighter::ReceiveDamages(iDamages);
    }
}

void Knight::DisplayFighterDatas()
{
    std::cout << "Fighter " << _FighterId + 1 << " : " << _Name << std::endl;
    std::cout << "HP : " << _Health << "\t\tShield : " << _Shield << std::endl;
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

void Knight::DealDamage(Fighter* iTarget)
{
    int Damages = _Weapon.GetDamages();
    int ChargeState = IsAffected(_ChargeName);

    if (ChargeState >= 0)
    {
        Damages *= 2;
        DecrementStatusById(ChargeState);
        EraseStatusIfFinished(ChargeState);
    }

    iTarget->ReceiveDamages(Damages);
    std::cout << "Fighter " << _FighterId + 1 << " : " << iTarget->GetName() << " ! You receive " << Damages << " damages !" << std::endl << std::endl;
}

void Knight::LaunchSkill(std::vector<Fighter*> iFightersList)
{
    // Add Cooldown on skill
    UseSkill();

    std::string Charge = SKILLCHARGENAME;
    std::cout << "Fighter " << _FighterId + 1 << " : " << _Name << " is affected for " << GetSkillEffect().GetDuration();

    int IsCharged = IsAffected(Charge);
    if (IsCharged >= 0)
    {
        std::cout << " more turn(s) by " << Charge << " !" << std::endl;
        // Increment Status Duration
        IncrementStatusById(IsCharged, GetSkillEffect().GetDuration());
    }
    else// Add Status
    {
        AddNewStatus(GetSkillEffect());
        std::cout << " turn(s) by " << Charge << " !" << std::endl;
    }
}

int Knight::GetTotaltHealth()
{
    return _Health + _Shield;
}