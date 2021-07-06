#include "Orc.h"

Orc::Orc(int iFighterId, std::string iName, int iHealth, Weapon iWeapon, std::vector<Status> iStatus) :
    Fighter(iFighterId, iName, iHealth, iWeapon, Skill(), iStatus)
{
	std::string StunName = SKILLSTUNNAME;
	Status SkillStatus = Status(StunName, 1);
	_Skill = Skill(StunName, 5, 20, SkillStatus);
}

void Orc::LaunchSkill(std::vector<Fighter*> iFightersList)
{
    Fighter* Target = NULL;
    if (iFightersList.size() > 2)
        Target = ChooseTarget(iFightersList, _FighterId);
    else
        Target = _FighterId == 0 ? iFightersList[1] : iFightersList[0];

    if (Target == NULL)
    {
        std::cout << "Skill cancelled !" << std::endl;
    }
    else // Launch Skill
    {
        // Add Cooldown on skill
        UseSkill();

        std::string Stun = SKILLSTUNNAME;
        std::cout << "Fighter " << Target->GetFighterId() + 1 << " : " << Target->GetName() << " is affected for " << GetSkillEffect().GetDuration();

        int IsStun = Target->IsAffected(Stun);
        if (IsStun >= 0)
        {
            std::cout << " more turn(s) by " << Stun << " !" << std::endl;
            IncrementStatusById(IsStun, GetSkillEffect().GetDuration());
        }
        else
        {
            Target->AddNewStatus(GetSkillEffect());
            std::cout << " turn(s) by " << Stun << " !" << std::endl;
        }
    }
}

Fighter* Orc::ChooseTarget(std::vector<Fighter*> iFighterList, int iActualFighterId, bool iCancelChoice)
{
    std::cout << "Choose your Target\n";

    for (int idOtherFighters = 0; idOtherFighters < (int)iFighterList.size() - 1; idOtherFighters++)
    {
        int FighterId = idOtherFighters >= iActualFighterId ? idOtherFighters + 1 : idOtherFighters;
        std::cout << idOtherFighters + 1 << " : " << iFighterList[FighterId]->GetName() << "\t\t";
    }

    if (iCancelChoice)
        std::cout << "C : Cancel\n";

    while (true)
    {
        if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) // Choice 1
            return 0 >= iActualFighterId ? iFighterList[1] : iFighterList[0];
        else if ((GetAsyncKeyState(0x32) || GetAsyncKeyState(VK_NUMPAD2)) && iFighterList.size() > 2) // Choice 2
            return 1 >= iActualFighterId ? iFighterList[2] : iFighterList[1];
        else if ((GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3)) && iFighterList.size() > 3 && iCancelChoice) // Choice 3
            return 2 >= iActualFighterId ? iFighterList[3] : iFighterList[2];
        else if (GetAsyncKeyState(0x43)) // Cancel
            return NULL;
    }

    return 0;
}