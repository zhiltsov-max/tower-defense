#ifndef LEVEL_EVENT_QUEUE_H
#define LEVEL_EVENT_QUEUE_H

#include "../../../Core/core.h"
#include "level_event.h"
#include "level_trigger.h"
#include <queue>


class TEventQueue
{
public:
	typedef uint ID;

	TEventQueue();
	
	void append(const TGameEvent& evt);
		
	const TGameEvent& getCurrentEvent() const;
	TGameEvent& getCurrentEvent();

	bool empty() const;

	void update();

	bool isTagRegistered(const TGameEvent::Tag& tag) const;
	ID getTagId(const TGameEvent::Tag& tag) const;
	ID registerTag(const TGameEvent::Tag& tag);
	void unregisterTag(const TGameEvent::Tag& tag);
private:
	std::queue<TGameEvent> queue;
	std::map<TGameEvent::Tag, ID> registeredTags;

	typedef std::list<TLevelTrigger*> Listeners;
	std::map<ID, Listeners> eventListeners;

	void notify();
};

#endif //LEVEL_EVENT_QUEUE_H
