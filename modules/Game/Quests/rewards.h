#ifndef __QUESTREWARDS_H__
#define __QUESTREWARDS_H__

#include "reward.h"

class TQuestRewards
{
public:
    typedef uint ClassId;

    TQuestRewards(const std::vector<ClassId>& ids);
	
	std::vector<string>&& getDescription() const;
	void grant() const;
private:
	typedef std::vector<TQuestReward> Data;
	Data data;
};

#endif
