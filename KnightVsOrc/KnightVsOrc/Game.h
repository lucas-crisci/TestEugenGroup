#ifndef GAME_H
#define GAME_H

#include "Fighter.h"
#include "Weapon.h"
#include "Skill.h"
#include "Status.h"

#include <vector>

class Game
{
public:
    Game(std::vector<Fighter> iFightersList, int iNbTurns = -1);
    Game();

    Fighter GetFighterById(int iId);
    std::vector<Fighter> GetAllFighters();
    
    void AddFighter(Fighter iNewFighter);
    void SetFighterById(Fighter iNewFighter, int iId);
    void SetAllFighters(std::vector<Fighter> iNewFighterList);

    void Start();

private:
    std::vector<Fighter> _FightersList;
    bool _LimitRounds;
    int _NbRounds;

    void SelectSkill();
    void DisplayFightersDatas();
    int ChooseTarget(int iActualFighterId);
    bool YesNoChoice();
    void PressEnter();
    void LaunchStun(int iIdFighter);
    void LaunchCharge(int iIdFighter);
};

#endif // GAME_H