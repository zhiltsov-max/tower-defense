#ifndef __QUESTREWARDSINFO_H__
#define __QUESTREWARDSINFO_H__

#include "..\..\..\Core\core.h"
#include "..\..\Info\object_info.h"
#include "..\..\Info\game_object_info_loader.h"
#include "reward.h"

class TQuestReward::Info : public TObjectInfo 
{
public:
	class Loader;

	Info();
	~Info();
protected:
	typedef TObjectInfo parent_type;
};

class TQuestReward::Info::Loader : public TGameObjectInfoLoader 
{
public:
	Loader();
	~Loader();

	void load(TQuestReward::Info* info, std::istream& source) const;
protected:
	typedef TGameObjectInfoLoader parent_type;
};

class TQuestRewardsInfo
{
public:
	typedef TQuestReward::Info Info;
	typedef Info::Value Value;

	static std::vector<string>&& getRequested(const string& source);
	TQuestRewardsInfo(const std::set<string>& requested);

    const Value& getParameter(TQuestReward::ClassId rewardId, const string& key) const;
private:
    std::map<TQuestReward::ClassId, Info> data;
};

#endif
