#ifndef __QUESTTRIGGERFACTORY_H__
#define __QUESTTRIGGERFACTORY_H__

#include "..\..\..\Core\core.h"
#include "trigger.h"

class TQuestTriggerFactory /* Pattern: Prototype & Factory */
{
public:	
	typedef uint ID;

	TQuestTriggerFactory();
	
	ID registerClass(ID id, TQuestTrigger const* prototype);	
	bool isClassRegistered(ID id) const;

	TQuestTrigger* create(ID id, const TNamedData<string>& args = TNamedData<string>()) const;
private:
	std::map<ID, TQuestTrigger const*> registeredClasses;
};

#endif