#ifndef __QUESTSINFO_H__
#define __QUESTSINFO_H__

#include "..\..\..\Core\core.h"
#include "..\..\Info\game_object_info_loader.h"
#include "..\..\Info\object_info.h"
#include "quest.h"
#include "taskinfo.h"
#include "rewardinfo.h"


class TLevelQuest::Info : public TObjectInfo 
{
public:
	class Loader;
protected:
	typedef TObjectInfo parent_type;
};

class TLevelQuest::Info::Loader : public TGameObjectInfoLoader 
{
public:
	void load(TLevelQuest::Info* info, std::istream& source) const;
protected:
	typedef TGameObjectInfoLoader parent_type;
};

class TQuestsInfo 
{
public:
	typedef TLevelQuest::Info Info;
	typedef Info::Value Value;

	TQuestsInfo();
	~TQuestsInfo();

    const Value& getParameter(TLevelQuest::ClassId questId, const string& key) const;
	const TQuestRewardsInfo& getRewards() const;
	const TQuestTasksInfo& getTasks() const;
private:
    std::map<TLevelQuest::ClassId, Info> data;

	TQuestTasksInfo tasks;
	TQuestRewardsInfo rewards;
};

#endif
