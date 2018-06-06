#ifndef __QUESTTASK_H__
#define __QUESTTASK_H__

#include "..\..\..\Core\core.h"
#include "triggers.h"

class TQuestTask
{
public:
    typedef uint ClassId;
	class Info;

	TQuestTask();
    TQuestTask(ClassId id_);
	
	uint getCurrent() const;
	uint getTotal() const;
	float getPrecent() const;
	const string& getDescription() const;
    ClassId getID() const;
	
	bool isCompleted() const;
	bool isFailed() const;
		
	void setCompleted(bool value);	
	void setFailed(bool value);	
	
	void update();
private:
	class Impl;
    ClassId id;

	uint current;
	uint total;

	bool failed;
	TQuestTriggers triggers;
};

#endif
