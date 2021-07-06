#ifndef KNIGHT_H
#define KNIGHT_H

#include "Fighter.h"

#include <string>
#include <vector>
#include <iostream>

class Knight : public Fighter
{
public:
	Knight(int iFighterId, std::string iName, int iHealth, Weapon iWeapon, int iShield, std::vector<Status> iStatus = std::vector<Status>());

	void ReceiveDamages(int iDamages);
	int GetShield();
	void DisplayFighterDatas();
	void DealDamage(Fighter* iTarget);
	void LaunchSkill(std::vector<Fighter*> iFightersList);

private:
	int _Shield;

	std::string _ChargeName = SKILLCHARGENAME;
};

#endif // KNIGHT_H