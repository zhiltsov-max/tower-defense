#include "task.h"
#include "controller.h"
#include "taskimpl.h"
#include "taskinfo.h"


TQuestTask::TQuestTask() 
{}
TQuestTask::TQuestTask(ClassId id_) :
	id(id_)
{
	total = *LevelQuestsController::getTasksInfo().getParameter(id, "total").as<int>();

	string raw_triggerID = *LevelQuestsController::getTasksInfo().getParameter(id, "triggers").as<string>();
	raw_triggerID = raw_triggerID.substr(2, raw_triggerID.size() - 2);
	std::vector<string> raw_triggerIDs = String::split(raw_triggerID, ',');
	std::vector<uint> triggerIDs(raw_triggerIDs.size());
	for(uint i = 0; i != raw_triggerIDs.size(); ++i) {
		triggerIDs[i] = std::stoi(raw_triggerIDs[i]);
	}
		
	triggers = TQuestTriggers(ids);

}

uint TQuestTask::getCurrent() const {
	return current;
}
uint TQuestTask::getTotal() const {
	return total;
}
float TQuestTask::getPrecent() const {
	return current * 100.0f / total;
}
const string& TQuestTask::getDescription() const {
	return *LevelQuestsController::getTasksInfo().getParameter(id, "description").as<string>();
}	
TQuestTask::ClassId TQuestTask::getID() const {
	return id;
}

bool TQuestTask::isCompleted() const {
	return (isFailed() == false) && (current == total);
}	
bool TQuestTask::isFailed() const {
	return failed;
}

void TQuestTask::setCompleted(bool value) {
	failed = false;
	if (value == true) {
		current = total;
	} else {
		current = 0;
	}
}

void TQuestTask::setFailed(bool value) {
	failed = value;
}

void TQuestTask::update() {
	Impl::invoke(this);
	triggers.update();
}
