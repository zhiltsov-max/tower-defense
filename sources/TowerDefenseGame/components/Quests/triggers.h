#ifndef __QUESTTRIGGERS_H__
#define __QUESTTRIGGERS_H__

#include "trigger.h"
#include "triggerfactory.h"

class TQuestTriggers
{
public:
	TQuestTriggers(const std::vector<uint>& ids);	
	void update();
private:
	typedef std::unique_ptr<TQuestTrigger> Trigger;
	typedef std::vector<Trigger> Data;
	Data data;
};

#endif