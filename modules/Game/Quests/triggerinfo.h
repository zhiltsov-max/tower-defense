#ifndef __QUESTTRIGGERSINFO_H__
#define __QUESTTRIGGERSINFO_H__

#include "..\..\..\Core\core.h"
#include "triggerfactory.h"
#include "..\..\Info\game_object_info_loader.h"
#include "..\..\Info\object_info.h"
#include "trigger.h"

class TQuestTrigger::Info : public TObjectInfo 
{
public:
	class Loader;

	Info();
	~Info();
protected:
	typedef TObjectInfo parent_type;
};

class TQuestTrigger::Info::Loader : public TGameObjectInfoLoader 
{
public:
	Loader();
	~Loader();

	void load(TQuestTrigger::Info* info, std::istream& source) const;
protected:
	typedef TGameObjectInfoLoader parent_type;
};

class TQuestTriggersInfo
{	
public:
	typedef TQuestTrigger::Info Info;
	typedef Info::Value Value;

	static std::vector<string>&& getRequested(const string& source);
	TQuestTriggersInfo(const std::set<string>& requested);

    const Value& getParameter(uint triggerId, const string& key) const;
	const TQuestTriggerFactory& getFactory() const;
private:
	std::map<uint, Info> data;
	TQuestTriggerFactory questTriggerFactory;
};

#include "triggerinfo.h"

#endif
