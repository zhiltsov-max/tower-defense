#ifndef __QUESTREWARD_H__
#define __QUESTREWARD_H__

#include "..\..\..\Core\core.h"

struct QuestRewardType { enum {
	undefined = 0,
	_min = 0,
	
	Level = 1, 
	Stage,	

	MobCountIncrease,
	MobHealthDecrease,
	MobSpeedDecrease,
	MobRewardIncrease,
	
	CreditsIncrease,
	
	BuildingsGrant,
	BuildingsCostDecrease,
	
	ResearchOpen,
	ResearchGrant,
	
	_max = ResearchGrant
}; };

class TQuestReward
{
public:
	class Info;

	TQuestReward();
	TQuestReward(uint id_);
		
	uint getID() const;
	uint getTypeID() const;	
	const string& getDescription() const;

	void grant() const;
private:
	class Impl;

	uint id;
	uint typeID;

	std::vector<string>&& getArgs() const;	
};

#endif