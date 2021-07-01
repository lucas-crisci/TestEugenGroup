// KnightVsOrc.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Fighter.h"
#include "Weapon.h"
#include "Skill.h"
#include "Status.h"
#include "Game.h"

#include <iostream>

#define MAXFIGHTERS 4;

// If you change in this class change it also in Game.cpp
#define SKILLSTUNNAME "Stun";
#define SKILLCHARGENAME "Charge";

using namespace std;

Game CreateDefaultGame()
{
    // Create fighter 1
    std::string Fighter1Name = "Knight";
    int Fighter1Health = 20;
    int Fighter1Shield = 50;

    std::string Fighter1WeaponName = "Sword";
    int Fighter1WeaponDamages = 5;
    Weapon Fighter1Weapon(Fighter1WeaponName, Fighter1WeaponDamages);

    std::string Fighter1SkillName = SKILLCHARGENAME;
    int Fighter1SkillCooldown = 3;
    int Fighter1SkillRate = 60;
    std::string Fighter1SkillEffectName = SKILLCHARGENAME;
    Status Fighter1SkillEffect(Fighter1SkillEffectName, 1);
    Skill Fighter1Skill(Fighter1SkillName, Fighter1SkillCooldown, Fighter1SkillRate, Fighter1SkillEffect);

    Fighter Fighter1(Fighter1Name, Fighter1Health, Fighter1Shield, Fighter1Weapon, Fighter1Skill);


    // Create fighter 2
    std::string Fighter2Name = "Orc";
    int Fighter2Health = 60;
    int Fighter2Shield = 0;

    std::string Fighter2WeaponName = "Axe";
    int Fighter2WeaponDamages = 8;
    Weapon Fighter2Weapon(Fighter2WeaponName, Fighter2WeaponDamages);

    std::string Fighter2SkillName = SKILLSTUNNAME;
    int Fighter2SkillCooldown = 5;
    int Fighter2SkillRate = 20;
    std::string Fighter2SkillEffectName = SKILLSTUNNAME;
    Status Fighter2SkillEffect(Fighter2SkillEffectName, 1);
    Skill Fighter2Skill(Fighter2SkillName, Fighter2SkillCooldown, Fighter2SkillRate, Fighter2SkillEffect);

    Fighter Fighter2(Fighter2Name, Fighter2Health, Fighter2Shield, Fighter2Weapon, Fighter2Skill);

    // Create Fighters list
    std::vector<Fighter> FightersList;
    FightersList.push_back(Fighter1);
    FightersList.push_back(Fighter2);
    
    return Game(FightersList);
}

int main()
{
    // TODO option to create choice


    // Create new default Game
    Game NewGame = CreateDefaultGame();
    NewGame.Start();
}
