#include "Status.h"

#include <iostream>
#include <string>

Status::Status(std::string iName, int iDuration)
{
    _Name = iName;
    _Duration = iDuration;
}

Status::Status()
{
    _Name = "Rage du gamer";
    _Duration = 8;
}

std::string Status::GetName()
{
    return _Name;
}

int Status::GetDuration()
{
    return _Duration;
}

void Status::DecrementDuration(int iDecrementValue)
{
    _Duration -= iDecrementValue;
}

void Status::IncrementDuration(int iIncrementValue)
{
    _Duration += iIncrementValue;
}