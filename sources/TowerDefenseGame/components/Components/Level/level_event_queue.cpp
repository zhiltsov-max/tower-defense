#include "level_event_queue.h"


TEventQueue::TEventQueue()
{}	
	
void TEventQueue::append(const TGameEvent& evt) {
	queue.push(evt);
}
		
const TGameEvent& TEventQueue::getCurrentEvent() const {
	queue.front();
}
TGameEvent& TEventQueue::getCurrentEvent() {
	queue.front();
}	
	
bool TEventQueue::empty() const {
	return queue.empty();
}
		
void TEventQueue::update() {
	if (queue.empty() == false) {
		notify();
		queue.pop();	
	}
}
		
void TEventQueue::notify() {
	const TGameEvent& current = getCurrentEvent();
	Listeners& listeners = eventListeners.at(registeredTags[current.getTag()]); // performance?
	for(auto it = listeners.begin(); it != listeners.end(); ++it) {
		(*it)->sendEvent(current);
	}
}
	
bool TEventQueue::isTagRegistered(const TGameEvent::Tag& tag) const {
	return eventListeners.count(tag) != 0;
}
TEventQueue::ID TEventQueue::getTagId(const TGameEvent::Tag& tag) const {
	if (isTagRegistered(tag) == false) {
		return EventType::undefined;
	} else {
		return registeredTags.at(tag);
	}
}
TEventQueue::ID TEventQueue::registerTag(const TGameEvent::Tag& tag) {
	if (isTagRegistered(tag) == true) {
		return getTagId(tag);
	} else {
		ID result = registeredTags.size() + 1;
		registeredTags[tag] = result;
		return result;
	}
}
void TEventQueue::unregisterTag(const TGameEvent::Tag& tag) {
	registeredTags.erase(tag);
}
