#ifndef __LEVELQUEST_H__
#define __LEVELQUEST_H__

#include "..\..\..\Core\core.h"
#include "rewards.h"
#include "tasks.h"

/*
	Data level for quests
*/
class TLevelQuest
{
public:
    typedef uint ClassId;
	class Info;
    enum class Importance {
        undefined = 0,
        _min = undefined,

        Usual = 1, Main,

        _max = Main
    };
    enum class State {
        Normal = 0,
        Completed,
        Failed
    };


	TLevelQuest();
    TLevelQuest(uint id_, bool active_ = false, Importance importance_ = QuestImportance::undefined);
		
	bool isCompleted() const;
	bool isFailed() const;
	bool isActive() const;
	
	void setCompleted(bool value);
	void setFailed(bool value);
	void setActive(bool value);
    void setImportance(Importance value);
	
	const std::vector<TQuestTask>& getProgress() const;
    ClassId getID() const;
	const string& getDescription() const;
	const string& getTitle() const;
	const string& getRewardDescription() const;
    Importance getImportance() const;
	
	void update();
private:
    ClassId id;
	TQuestTasks tasks;
	TQuestRewards rewards;
	bool active;
    Importance importance;
};

#endif
