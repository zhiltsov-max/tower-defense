#ifndef __QUESTTASKSINFO_H__
#define __QUESTTASKSINFO_H__

#include "..\..\..\Core\core.h"
#include "..\..\Info\game_object_info_loader.h"
#include "..\..\Info\object_info.h"
#include "task.h"
#include "triggerinfo.h"

class TQuestTask::Info : public TObjectInfo 
{
public:
	class Loader;

	Info();
	~Info();
protected:
	typedef TObjectInfo parent_type;
};

class TQuestTask::Info::Loader : public TGameObjectInfoLoader 
{
public:
	Loader();
	~Loader();

	void load(TQuestTask::Info* info, std::istream& source) const;
protected:
	typedef TGameObjectInfoLoader parent_type;
};

class TQuestTasksInfo
{
public:
	typedef TQuestTask::Info Info;
	typedef Info::Value Value;

	static std::vector<string>&& getRequested(const string& source);
	TQuestTasksInfo(const std::set<string>& requested);

    const Value& getParameter(TQuestTask::ClassId taskId, const string& key) const;
	const TQuestTriggersInfo& getTriggers() const;
private:
    std::map<TQuestTask::ClassId, Info> data;
	TQuestTriggersInfo triggers;
};

#endif
