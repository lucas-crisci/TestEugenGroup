#ifndef KNIGHTVSORC_H
#define KNIGHTVSORC_H

#include "Fighter.h"
#include "Weapon.h"
#include "Skill.h"
#include "Status.h"
#include "Game.h"

#include <string>

class KnightVsOrc
{
private:
    int main();
    Game CreateDefaultGame();
    Status CreateCustomStatus();
    Weapon CreateCustomWeapon();
    Game CreateCustomGame();
};

#endif // KNIGHTVSORC_H