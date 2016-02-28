#include "triggerfactory.h"


TQuestTriggerFactory::TQuestTriggerFactory() 
{}
	
ID TQuestTriggerFactory::registerClass(ID id, TQuestTrigger const* prototype) {
	if (prototype == nullptr) {
		throw_("Failed to register trigger class: prototype is empty.", "TQuestTriggerFactory::registerClass");
	}
	registeredClasses[id] = prototype;
}
	
bool isClassRegistered(ID id) const {
	return registeredClasses.count(id) != 0;
}

TQuestTrigger* TQuestTriggerFactory::create(ID id, const TNamedData<string>& args) const {
	if (isClassRegistered(id) == false) {
		throw_("Trigger #" + std::to_string((long long)id) + " was not registered.", "TQuestTriggerFactory::create");
	}
	TQuestTrigger* trigger = registeredClasses.at(id)->clone();
	trigger->initialize(args);
	return trigger;
}