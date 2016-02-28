#ifndef LEVEL_QUESTS_H
#define LEVEL_QUESTS_H

#include "..\..\..\Core\core.h"
#include "quest.h"

/*
	Logic level for quests
*/
class TLevelQuests
{
public:	
	TLevelQuests();	
	void loadForStage(const TNamedData<string>& source);	
	
    void setQuest(TLevelQuest::ClassId id, const TLevelQuest& value);
    const TLevelQuest& getQuest(TLevelQuest::ClassId id) const;
    TLevelQuest& getQuest(TLevelQuest::ClassId id);
	
	void setCompleted(bool value);
	void setFailed(bool value);
		
	bool isStageCompleted() const;
	bool isStageFailed() const;
	
	bool isLevelCompleted() const;
	bool isLevelFailed() const;
	
	void update();
private:
	const char partsSeparator = ',';

	int summaryState;
    typedef std::map<TLevelQuest::ClassId, TLevelQuest> Data;
	Data data;
};

#endif //LEVEL_QUESTS_H
