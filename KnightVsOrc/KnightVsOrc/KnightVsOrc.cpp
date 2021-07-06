// KnightVsOrc.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "InputOutput.h"
#include "Fighter.h"
#include "Knight.h"
#include "Orc.h"
#include "Weapon.h"
#include "Skill.h"
#include "Status.h"
#include "Game.h"

#include <Windows.h>
#include <iostream>
#include<stdio.h>

#define MAXFIGHTERS 4;

#define SKILLSTUNNAME "Stun";
#define SKILLCHARGENAME "Charge";

InputOutput _IO;
using namespace std;

Game CreateDefaultGame()
{
    int IdFighter = 0;

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

    Knight* Fighter1 = new Knight(IdFighter++, Fighter1Name, Fighter1Health, Fighter1Weapon, Fighter1Shield);


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

    Orc* Fighter2 = new Orc(IdFighter++, Fighter2Name, Fighter2Health, Fighter2Weapon);

    // Create Fighters list
    std::vector<Fighter*> FightersList;
    FightersList.push_back(Fighter1);
    FightersList.push_back(Fighter2);
    
    return Game(FightersList);
}

int main()
{
    Game NewGame = CreateDefaultGame();

    NewGame.Start();
}
