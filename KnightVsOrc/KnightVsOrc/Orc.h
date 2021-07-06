#ifndef ORC_H
#define ORC_H

#include "Fighter.h"
#include "InputOutput.h"

class Orc : public Fighter
{
public:
	Orc(int iFighterId, std::string iName, int iHealth, Weapon iWeapon, std::vector<Status> iStatus = std::vector<Status>());

	void LaunchSkill(std::vector<Fighter*> iFightersList);

private:
	InputOutput _IO;

	Fighter* ChooseTarget(std::vector<Fighter*> iFighterList, int iActualFighterId, bool iCancelChoice = true);
};

#endif // ORC_H