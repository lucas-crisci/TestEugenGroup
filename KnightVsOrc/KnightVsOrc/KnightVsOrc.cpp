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

Game CreateDefaultGame(int iNbRounds)
{
    int IdFighter = 0;

    // Create fighter 1
    std::string Fighter1Name = "Knight";
    int Fighter1Health = 20;
    int Fighter1Shield = 50;

    std::string Fighter1WeaponName = "Sword";
    int Fighter1WeaponDamages = 5;
    Weapon Fighter1Weapon(Fighter1WeaponName, Fighter1WeaponDamages);

    Knight* Fighter1 = new Knight(IdFighter++, Fighter1Name, Fighter1Health, Fighter1Weapon, Fighter1Shield);


    // Create fighter 2
    std::string Fighter2Name = "Orc";
    int Fighter2Health = 60;

    std::string Fighter2WeaponName = "Axe";
    int Fighter2WeaponDamages = 8;
    Weapon Fighter2Weapon(Fighter2WeaponName, Fighter2WeaponDamages);

    Orc* Fighter2 = new Orc(IdFighter++, Fighter2Name, Fighter2Health, Fighter2Weapon);

    // Create Fighters list
    std::vector<Fighter*> FightersList;
    FightersList.push_back(Fighter1);
    FightersList.push_back(Fighter2);
    
    return Game(FightersList, iNbRounds);
}

int NbRounds()
{
    bool ChoiceRounds = _IO.ABChoices("5", "10");
    if (ChoiceRounds)
        return 5;
    else
        return 10;
}

int main()
{
    std::cout << "Do you want to add a limit to the number of rounds?" << std::endl;
    bool Choice = _IO.YesNoChoice();

    int iNbRounds = Choice ? NbRounds() : -1;

    Game NewGame = CreateDefaultGame(iNbRounds);
    NewGame.Start();
}
