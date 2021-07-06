#include "Game.h"

Game::Game(std::vector<Fighter*> iFightersList, int iNbRounds)
{
    _FightersList = iFightersList;
    _LimitRounds = iNbRounds >= 0 ? true : false;
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
    int TourCounter = 0;
    int AvailableFighters = _FightersList.size();

    _IO.Refresh();
    DisplayFightersDatas();

    while (!EndGame && (TourCounter < _NbRounds || !_LimitRounds))
    {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Tour " << TourCounter+1 << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        
        std::cout << "Start skill selection !" << std::endl;
        _IO.PressEnter();
        SelectSkill();

        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Tour " << TourCounter+1 << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;

        std::cout << "Start attack round !" << std::endl;
        _IO.PressEnter();
        SelectAttackTarget();

        int RoundResult = CheckIfEndGame();
        if (RoundResult >= 0)
        {
            std::cout << "Fighter " << RoundResult + 1 << " : " << _FightersList[RoundResult]->GetName() << " ! You are dead, GAME OVER ! " << std::endl << std::endl;
            AvailableFighters--;
            if (AvailableFighters <= 1)
            {
                EndGame = true;
                _IO.PressEnter();
            }
        }

        TourCounter++;
    }

    if (!EndGame)
        std::cout << "Game over! No winner!" << std::endl;
}

void Game::SelectSkill()
{
    for (int idFighter = 0; idFighter < (int)_FightersList.size(); idFighter++)
    {
        DisplayFightersDatas();
        std::string Stun = SKILLSTUNNAME;
        std::string Charge = SKILLCHARGENAME;
        int IsStun = _FightersList[idFighter]->IsAffected(Stun);

        if (IsStun >= 0)
        {
            std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter]->GetName() << " ! You are stunned ! " << std::endl << std::endl;
        }
        else if (_FightersList[idFighter]->GetSkill().GetActualCooldown() == 0)
        {
            std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter]->GetName() << " ! Do you want to launch your skill \"" << _FightersList[idFighter]->GetSkill().GetName() << "\" ?" << std::endl;
            bool Choice = _IO.YesNoChoice();
            if (Choice)
            {
                srand(time(NULL));
                int RandomNb = (rand() % 100) + 1;
                std::cout << RandomNb << "/" << _FightersList[idFighter]->GetSkill().GetRate();
                if (RandomNb <= _FightersList[idFighter]->GetSkill().GetRate())
                {
                    std::cout << std::endl;
                
                    _FightersList[idFighter]->LaunchSkill(_FightersList);
                }
                else
                {
                    std::cout << " Failed dice roll !\n";
                    _FightersList[idFighter]->UseSkill();
                }
            }
            else
            {
                std::cout << "You don't launch your skill." << std::endl << std::endl;
                _FightersList[idFighter]->DecrementSkillCooldown();
            }
        }
        else
        {
            _FightersList[idFighter]->DecrementSkillCooldown();
            std::cout << "Player " << idFighter + 1 << " : " << _FightersList[idFighter]->GetName() << " ! Your skill is not ready, it will be ready in " << _FightersList[idFighter]->GetSkill().GetActualCooldown() << " rounds" << std::endl << std::endl;
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
        int IsStun = _FightersList[idFighter]->IsAffected(Stun);

        if (IsStun >= 0)
        {
            std::cout << "Fighter " << idFighter + 1 << " : " << _FightersList[idFighter]->GetName() << " ! You are stunned ! " << std::endl << std::endl;
            // Decrement status duration and Erase if finished
            _FightersList[idFighter]->DecrementStatusById(IsStun);
            _FightersList[idFighter]->EraseStatusIfFinished(IsStun);
        }
        else
        {
            // Select Target
            int TargetId = -1;
            if (_FightersList.size() > 2)
                TargetId = ChooseTarget(idFighter, false);
            else
                TargetId = idFighter == 0 ? 1 : 0;

            // Calcul and apply damages
            _FightersList[idFighter]->DealDamage(_FightersList[TargetId]);
        }

        _IO.PressEnter();
    }
}

void Game::DisplayFightersDatas()
{
    for (int idFighter = 0; idFighter < (int)_FightersList.size(); idFighter++)
    {
        _FightersList[idFighter]->DisplayFighterDatas();
    }
}

Fighter* Game::GetFighterById(int iId)
{
    if (iId < (int)_FightersList.size())
        return _FightersList[iId];

    Fighter* DefaultFighter = new Fighter();

    return DefaultFighter;
}

std::vector<Fighter*> Game::GetAllFighters()
{
    return _FightersList;
}

void Game::AddFighter(Fighter* iNewFighter) 
{
    _FightersList.push_back(iNewFighter);
}

void Game::SetFighterById(Fighter* iNewFighter, int iId)
{
    _FightersList[iId] = iNewFighter;
}

void Game::SetAllFighters(std::vector<Fighter*> iNewFighterList)
{
    _FightersList = iNewFighterList;
}

int Game::ChooseTarget(int iActualFighterId, bool iCancelChoice)
{
    std::cout << "Choose your Target\n";

    for (int idOtherFighters = 0; idOtherFighters < (int)_FightersList.size() - 1; idOtherFighters++)
    {
        int FighterId = idOtherFighters >= iActualFighterId ? idOtherFighters + 1 : idOtherFighters;
        std::cout << idOtherFighters + 1 << " : " << _FightersList[FighterId]->GetName() << "\t\t";
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

int Game::CheckIfEndGame()
{
    for (int idFighters = 0; idFighters < (int)_FightersList.size(); idFighters++)
    {
        if (_FightersList[idFighters]->GetTotaltHealth() <= 0)
            return idFighters;
    }
    return -1;
}