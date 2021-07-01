#include "Game.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

// If you change in this class change it also in KnightVsOrc.cpp
#define SKILLSTUNNAME "Stun";
#define SKILLCHARGENAME "Charge";

Game::Game(std::vector<Fighter> iFightersList, int iNbRounds)
{
    _FightersList = iFightersList;
    _LimitRounds = true;
    _NbRounds = iNbRounds;
}

Game::Game()
{
    _LimitRounds = false;
    _NbRounds = 0;
}

void Game::Start()
{
    bool EndGame = false;
    int TourCounter = 1;

    DisplayFightersDatas();

    while (!EndGame || (TourCounter < _NbRounds && _LimitRounds))
    {
        std::cout << std::endl << "--------------------------------------------------" << std::endl;
        std::cout << "Tour " << TourCounter << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        
        std::cout << "Start skill selection !" << std::endl;
        PressEnter();
        SelectSkill();

        std::cout << "Start attack target selection !" << std::endl;
        PressEnter();

        TourCounter++;
        //EndGame = true;
    }
}

void Game::SelectSkill()
{
    for (int idFighter = 0; idFighter < (int)_FightersList.size(); idFighter++)
    {
        DisplayFightersDatas();
        std::string Stun = SKILLSTUNNAME;
        std::string Charge = SKILLCHARGENAME;
        int IsStun = _FightersList[idFighter].IsAffected(Stun);

        if (IsStun >= 0)
        {
            std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << " ! You are stunned ! " << std::endl << std::endl;
            // Decrement status duration and Erase if finished
            _FightersList[idFighter].DecrementStatusById(IsStun);
            _FightersList[idFighter].EraseStatusIfFinished(IsStun);
        }
        else if (_FightersList[idFighter].GetSkill().GetActualCooldown() == 0)
        {
            std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << " ! Do you want to launch your skill \"" << _FightersList[idFighter].GetSkill().GetName() << "\" ?" << std::endl;
            bool Choice = YesNoChoice();
            if (Choice)
            {
                std::string SkillName = _FightersList[idFighter].GetSkill().GetName();
                //TODO créer méthode pour lancer lancer Charge
                if(_FightersList[idFighter].GetSkill().GetName() == Stun)
                    LaunchStun(idFighter);
                else if (_FightersList[idFighter].GetSkill().GetName() == Charge)
                    LaunchCharge(idFighter);
            }
            else
            {
                std::cout << "You don't launch your skill." << std::endl << std::endl;
            }
        }
        else
        {
            _FightersList[idFighter].GetSkill().DecrementActualCooldown();
            std::cout << "Player " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << " ! Your skill is not ready, it will be ready in " << _FightersList[idFighter].GetSkill().GetActualCooldown() << " rounds" << std::endl << std::endl;
            Sleep(1000);
        }

        PressEnter();
    }
}

void Game::DisplayFightersDatas()
{
    for (int idFighter = 0; idFighter < (int)_FightersList.size(); idFighter++)
    {
        std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << std::endl;
        std::cout << "HP : " << _FightersList[idFighter].GetHealth() << "\tShield : " << _FightersList[idFighter].GetShield() << std::endl;
        std::cout << "Weapon : " << _FightersList[idFighter].GetWeapon().GetName() << "\tDamages : " << _FightersList[idFighter].GetWeapon().GetDamages() << std::endl;
        std::cout << "Skill : " << _FightersList[idFighter].GetSkill().GetName() << "\tCoolDown : " << _FightersList[idFighter].GetSkill().GetActualCooldown() << " / " << _FightersList[idFighter].GetSkill().GetCooldown() << std::endl;

        if (0 < _FightersList[idFighter].GetAllStatus().size())
        {
            std::cout << "Status : ";
            std::vector<Status> FighterStatus = _FightersList[idFighter].GetAllStatus();
            for (int idStatus = 0; idStatus < (int)FighterStatus.size(); idStatus++)
            {
                std::cout << FighterStatus[idStatus].GetName();
                if (idStatus < (int)FighterStatus.size() - 1)
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

Fighter Game::GetFighterById(int iId)
{
    if (iId < (int)_FightersList.size())
        return _FightersList[iId];

    return Fighter();
}

std::vector<Fighter> Game::GetAllFighters()
{
    return _FightersList;
}

void Game::AddFighter(Fighter iNewFighter) 
{
    _FightersList.push_back(iNewFighter);
}

void Game::SetFighterById(Fighter iNewFighter, int iId)
{
    _FightersList[iId] = iNewFighter;
}

void Game::SetAllFighters(std::vector<Fighter> iNewFighterList)
{
    _FightersList = iNewFighterList;
}

int Game::ChooseTarget(int iActualFighterId)
{
    std::cout << "Choose your Target\n";

    for (int idOtherFighters = 0; idOtherFighters < (int)_FightersList.size() - 1; idOtherFighters++)
    {
        int FighterId = idOtherFighters >= iActualFighterId ? idOtherFighters + 1 : idOtherFighters;
        std::cout << idOtherFighters + 1 << " : " << _FightersList[FighterId].GetName() << "\t\t";
    }

    std::cout << "C : Cancel\n";

    while (true)
    {
        if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) // Choice 1
            return 0 >= iActualFighterId ? 1 : 0;
        else if ((GetAsyncKeyState(0x32) || GetAsyncKeyState(VK_NUMPAD2)) && _FightersList.size() > 2) // Choice 2
            return 1 >= iActualFighterId ? 2 : 1;
        else if ((GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3)) && _FightersList.size() > 3) // Choice 3
            return 2 >= iActualFighterId ? 3 : 2;
        else if (GetAsyncKeyState(0x43)) // Cancel
            return -1;
    }

    return 0;
}

bool Game::YesNoChoice()
{
    std::cout << "y = yes / n = no" << std::endl;
    while (true)
    {
        if (GetAsyncKeyState(0x59)) // Y Choice
            return true;
        else if (GetAsyncKeyState(0x4E)) // N Choice
            return false;
    }
}

void Game::PressEnter()
{
    std::cout << "\nPress Enter to continue" << std::endl;
    
    bool EnterPressed = false;
    bool EnterReleased = false;
    while (!EnterPressed)
    {
        if (GetAsyncKeyState(VK_RETURN))
        {
            EnterPressed = true;
            while (!EnterReleased)
            {
                if (!GetAsyncKeyState(VK_RETURN))
                    EnterReleased = true;
            }
        }
    }

    system("CLS");
}

void Game::LaunchStun(int iIdFighter)
{
    int TargetId = -1;
    if (_FightersList.size() > 2)
        TargetId = ChooseTarget(iIdFighter);
    else
        TargetId = iIdFighter == 0 ? 1 : 0;

    if (TargetId < 0)
    {
        std::cout << "Skill cancelled !" << std::endl;
    }
    else // Launch Skill
    {
        // Add Cooldown on skill
        _FightersList[iIdFighter].UseSkill();

        std::string Stun = SKILLSTUNNAME;
        int IsStun = _FightersList[TargetId].IsAffected(Stun);
        if (IsStun >= 0)
        {
            std::cout << "Fighter " << TargetId+1 << " : " << _FightersList[TargetId].GetName() << " is affected for " << _FightersList[iIdFighter].GetSkillEffect().GetDuration() << " more turn(s) by " << Stun << " !" << std::endl;
            _FightersList[iIdFighter].IncrementStatusById(IsStun, _FightersList[iIdFighter].GetSkillEffect().GetDuration());
        }
        else
        {
            _FightersList[TargetId].AddNewStatus(_FightersList[iIdFighter].GetSkillEffect());
            std::cout << "Fighter " << TargetId+1 << " : " << _FightersList[TargetId].GetName() << " is affected for " << _FightersList[iIdFighter].GetSkillEffect().GetDuration() << " turn(s) by " << Stun << " !" << std::endl;
        }
    }
}

void Game::LaunchCharge(int iIdFighter)
{
    // Add Cooldown on skill
    _FightersList[iIdFighter].UseSkill();

    std::string Charge = SKILLCHARGENAME;
    int IsCharged = _FightersList[iIdFighter].IsAffected(Charge);
    if (IsCharged >= 0)
    {
        std::cout << "Fighter " << iIdFighter+1 << " : " << _FightersList[iIdFighter].GetName() << " is affected for " << _FightersList[iIdFighter].GetSkillEffect().GetDuration() << " more turn(s) by " << Charge << " !" << std::endl;
        // Increment Status Duration
        _FightersList[iIdFighter].IncrementStatusById(IsCharged, _FightersList[iIdFighter].GetSkillEffect().GetDuration());
    }
    else// Add Status
    {
        _FightersList[iIdFighter].AddNewStatus(_FightersList[iIdFighter].GetSkillEffect());
        std::cout << "Fighter " << iIdFighter+1 << " : " << _FightersList[iIdFighter].GetName() << " is affected for " << _FightersList[iIdFighter].GetSkillEffect().GetDuration() << " turn(s) by " << Charge << " !" << std::endl;
    }
}