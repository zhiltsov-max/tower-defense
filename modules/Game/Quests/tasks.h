#ifndef __QUESTTASKS_H__
#define __QUESTTASKS_H__

#include "..\..\..\Core\core.h"
#include "task.h"

class TQuestTasks
{
public:
	TQuestTasks();
    TQuestTasks(const std::vector<TQuestTask::ClassId>& ids);
		
	const std::vector<TQuestTask>& getProgress() const;

	bool isCompleted() const;
	bool isFailed() const;
		
	void setCompleted(bool value);	
	void setFailed(bool value);	
	
	void update();
private:
	typedef std::vector<TQuestTask> Data;
	Data tasks;
};

#endif
