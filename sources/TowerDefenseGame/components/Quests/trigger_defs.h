#ifndef __QUESTTRIGGERDEFS_H__
#define __QUESTTRIGGERDEFS_H__

#include "..\..\..\Core\core.h"
#include "trigger.h"
#include "..\event_defs.h"

class TMobSequence
{
public:
	TMobSequence();	
	TMobSequence(const TNamedData<string>& source);	
	/*
		If there's no next -1 is returned.
	*/
	int makeStep();	
	void restart();	

	bool isCompleted() const;
	size_t length() const;
	uint getDelay(int position = 0) const;
private:
	const char elementsSeparator = ',';
	const char mobCountSeparator = '*';

	struct Entry {
		int mobId;
		int count;

		Entry(int mobId_, int count_) :
			mobId(mobId_), count(count_)
		{}
	};
	std::vector<Entry> sequence;

	int position;
	size_t currentEntry;
	uint delay;	


	size_t size() const;
};

class TQuestTrigger_MobSpawn : public TQuestTrigger
{
public:
	const TGameEvent::Tag EVENT_TAG_MOB_SPAWNED;

	TQuestTrigger_MobSpawn();
	TQuestTrigger_MobSpawn(const TMobSequence& sequence_, uint pathId_);
	void initialize(const TNamedData<string>& args);
	TLevelTrigger* clone() const;

	static uint getMobDelay(int position, const TMobSequence& sequence);

	uint getTimer() const;
	void setTimer(uint value);

	uint getPathId() const;
	void setPathId(uint value);
	
	const TMobSequence& getSequence() const;
	void setSequence(const TMobSequence& value);
	
	void update();
private:	
	uint timer;
	uint pathId;
	
	TMobSequence sequence;
};

#endif