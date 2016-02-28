#include "trigger.h"


TLevelTrigger::TLevelTrigger() 
{}

TLevelTrigger::~TLevelTrigger() 
{}

void TLevelTrigger::sendEvent(const TGameEvent& evt) {
	handleEvent(evt);
}

void TLevelTrigger::addEventHandler(const EventTag& tag, const TEventHandler& handler) {
	eventHandles[tag] = handler;
}
void TLevelTrigger::removeEventHandler(const EventTag& tag) {
	eventHandles.erase(tag);
}

void TLevelTrigger::handleEvent(const TGameEvent& evt) {
	if (acceptsEvent(evt) == true) {
		eventHandles[evt.getType()].invoke(evt);
	} else {
		DebugTools::log("Trigger does not accept event tagged '" + evt.getType() + "'.", "TLevelTrigger::handleEvent");
	}
}

const TEventQueue& TLevelTrigger::getQueue() {
	return LevelHelper::getLevelInstance().getProgress().getEventQueue();
}
TEventQueue& TLevelTrigger::getQueue() {
	return LevelHelper::getLevelInstance().getProgress().getEventQueue();
}

void TLevelTrigger::registerEvent(const string& tag) {
	getQueue().registerTag(tag);
}

bool TLevelTrigger::acceptsEvent(const TGameEvent& evt) const {
	return eventHandles.count(evt.getType()) != 0;
}