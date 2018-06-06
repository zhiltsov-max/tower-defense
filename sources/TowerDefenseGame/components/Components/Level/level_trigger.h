#ifndef __LEVELTRIGGER_H__
#define __LEVELTRIGGER_H__

#include "..\..\Core\core.h"
#include "helper.h"
#include "event_defs.h"

class TLevelTrigger /*Abstract*/
{
public:
	typedef TGameEvent::Tag EventTag;
	typedef TEventHandler EventHandle;

	TLevelTrigger();
	virtual ~TLevelTrigger();

	virtual void initialize(const TNamedData<string>& args) = 0;
	virtual TLevelTrigger* clone() = 0;
	virtual void update() = 0;

	virtual void sendEvent(const TGameEvent& evt);

	void addEventHandler(const EventTag& tag, const TEventHandler& handler);	
	void removeEventHandler(const EventTag& tag);
private:
	std::map<EventTag, EventHandle> eventHandles;
			
	static const TEventQueue& getQueue();
	static TEventQueue& getQueue();

	void handleEvent(const TGameEvent& evt);
	void registerEvent(const string& tag);		
	bool acceptsEvent(const TGameEvent& evt) const;
};

#endif