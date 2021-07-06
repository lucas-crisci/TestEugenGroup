#ifndef GAME_H
#define GAME_H

#include "Fighter.h"
#include "Weapon.h"
#include "Skill.h"
#include "Status.h"
#include "InputOutput.h"

#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <time.h>

class Game
{
public:
    Game(std::vector<Fighter*> iFightersList, int iNbTurns = -1);
    Game();

    Fighter* GetFighterById(int iId);
    std::vector<Fighter*> GetAllFighters();
    
    void AddFighter(Fighter* iNewFighter);
    void SetFighterById(Fighter* iNewFighter, int iId);
    void SetAllFighters(std::vector<Fighter*> iNewFighterList);

    void Start();

private:
    std::vector<Fighter*> _FightersList;
    bool _LimitRounds;
    int _NbRounds;
    InputOutput _IO;

    void SelectSkill();
    void SelectAttackTarget();
    void DisplayFightersDatas();
    int ChooseTarget(int iActualFighterId, bool iCancelChoice = true);
    int CheckIfEndGame();
};

#endif // GAME_H