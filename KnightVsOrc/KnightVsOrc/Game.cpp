#include "Game.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>

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
    int AvailableFighters = _FightersList.size();

    DisplayFightersDatas();

    while (!EndGame || (TourCounter < _NbRounds && _LimitRounds))
    {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Tour " << TourCounter << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        
        std::cout << "Start skill selection !" << std::endl;
        _IO.PressEnter();
        SelectSkill();

        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Tour " << TourCounter << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;

        std::cout << "Start attack target selection !" << std::endl;
        _IO.PressEnter();
        SelectAttackTarget();

        int RoundResult = CheckIfEndGame();
        if (RoundResult >= 0)
        {
            std::cout << "Fighter " << RoundResult + 1 << " : " << _FightersList[RoundResult].GetName() << " ! You are dead, GAME OVER ! " << std::endl << std::endl;
            AvailableFighters--;
            if (AvailableFighters <= 1)
            {
                EndGame = true;
                _IO.PressEnter();
            }
        }

        TourCounter++;
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
        }
        else if (_FightersList[idFighter].GetSkill().GetActualCooldown() == 0)
        {
            std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << " ! Do you want to launch your skill \"" << _FightersList[idFighter].GetSkill().GetName() << "\" ?" << std::endl;
            bool Choice = _IO.YesNoChoice();
            if (Choice)
            {
                int RandomNb = rand() % 100 + 1;
                if (RandomNb <= _FightersList[idFighter].GetSkill().GetRate())
                {
                    std::string SkillName = _FightersList[idFighter].GetSkill().GetName();
                
                    if(_FightersList[idFighter].GetSkill().GetName() == Stun)
                        LaunchStun(idFighter);
                    else if (_FightersList[idFighter].GetSkill().GetName() == Charge)
                        LaunchCharge(idFighter);
                }
                else
                {
                    std::cout << "Failed dice roll !\n";
                    _FightersList[idFighter].UseSkill();
                }
            }
            else
            {
                std::cout << "You don't launch your skill." << std::endl << std::endl;
                _FightersList[idFighter].GetSkill().DecrementActualCooldown();
            }
        }
        else
        {
            _FightersList[idFighter].DecrementSkillCooldown();
            std::cout << "Player " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << " ! Your skill is not ready, it will be ready in " << _FightersList[idFighter].GetSkill().GetActualCooldown() << " rounds" << std::endl << std::endl;
        }

        _IO.PressEnter();
    }
}

void Game::SelectAttackTarget()
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
        else
        {
            // Select Target
            int TargetId = -1;
            if (_FightersList.size() > 2)
                TargetId = ChooseTarget(idFighter, false);
            else
                TargetId = idFighter == 0 ? 1 : 0;

            // Calcul damages
            int Damages = _FightersList[idFighter].GetWeapon().GetDamages();

            int IsCharged = _FightersList[idFighter].IsAffected(Charge);
            if (IsCharged >= 0)
            {
                Damages *= 2;
                _FightersList[idFighter].DecrementStatusById(IsCharged);
                _FightersList[idFighter].EraseStatusIfFinished(IsCharged);
            }

            // Apply Damages
            std::cout << "Fighter " << TargetId + 1 << " : " << _FightersList[TargetId].GetName() << " ! You receive " << Damages << " damages !" << std::endl << std::endl;
            _FightersList[TargetId].ReceiveDamages(Damages);
        }

        _IO.PressEnter();
    }
}

void Game::DisplayFightersDatas()
{
    for (int idFighter = 0; idFighter < (int)_FightersList.size(); idFighter++)
    {
        std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter].GetName() << std::endl;
        std::cout << "HP : " << _FightersList[idFighter].GetHealth() << "\t\tShield : " << _FightersList[idFighter].GetShield() << std::endl;
        std::cout << "Weapon : " << _FightersList[idFighter].GetWeapon().GetName() << "\t\tDamages : " << _FightersList[idFighter].GetWeapon().GetDamages() << std::endl;
        std::cout << "Skill : " << _FightersList[idFighter].GetSkill().GetName() << "\t\tCoolDown : " << _FightersList[idFighter].GetSkill().GetActualCooldown() << " / " << _FightersList[idFighter].GetSkill().GetCooldown() << std::endl;

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

int Game::ChooseTarget(int iActualFighterId, bool iCancelChoice)
{
    std::cout << "Choose your Target\n";

    for (int idOtherFighters = 0; idOtherFighters < (int)_FightersList.size() - 1; idOtherFighters++)
    {
        int FighterId = idOtherFighters >= iActualFighterId ? idOtherFighters + 1 : idOtherFighters;
        std::cout << idOtherFighters + 1 << " : " << _FightersList[FighterId].GetName() << "\t\t";
    }

    if(iCancelChoice)
        std::cout << "C : Cancel\n";

    while (true)
    {
        if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) // Choice 1
            return 0 >= iActualFighterId ? 1 : 0;
        else if ((GetAsyncKeyState(0x32) || GetAsyncKeyState(VK_NUMPAD2)) && _FightersList.size() > 2) // Choice 2
            return 1 >= iActualFighterId ? 2 : 1;
        else if ((GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3)) && _FightersList.size() > 3 && iCancelChoice) // Choice 3
            return 2 >= iActualFighterId ? 3 : 2;
        else if (GetAsyncKeyState(0x43)) // Cancel
            return -1;
    }

    return 0;
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

int Game::CheckIfEndGame()
{
    for (int idFighters = 0; idFighters < (int)_FightersList.size(); idFighters++)
    {
        if (_FightersList[idFighters].GetHealth() <= 0)
            return idFighters;
    }
    return -1;
}