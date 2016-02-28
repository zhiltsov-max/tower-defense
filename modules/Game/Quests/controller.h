#ifndef __QUESTCONTROLLER_H__
#define __QUESTCONTROLLER_H__

#include "..\helper.h"
#include "quest.h"
#include "info.h"

class LevelQuestsController /*Abstract*/
{
public:
    static const TQuestsInfo::Value& getParameter(TLevelQuest::ClassId id, const string& key) {
		return getInfo().getParameter(id, key);
	}
    static TQuestsInfo::Value& getParameter(TLevelQuest::ClassId id, const string& key) {
		return getInfo().getParameter(id, key);
	}

	static TQuestsInfo& getInfo() {
		return getLevel().getInfo().getGameObjectsInfo().getQuestsInfo();
	}
	
	static const TQuestRewardsInfo& getRewardsInfo() {
		return getInfo().getRewards();
	}
	
	static const TQuestTasksInfo& getTasksInfo() {
		return getInfo().getTasks();
	}

	LevelQuestsController() = delete;
private:
	static TLevel& getLevel() {
		return LevelHelper::getLevelInstance();
	}
};

#endif
