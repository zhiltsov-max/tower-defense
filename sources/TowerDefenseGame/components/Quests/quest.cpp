#include "quest.h"
#include "controller.h"
#include "tasks.h"
#include "rewards.h"

TLevelQuest::TLevelQuest() 
{}

TLevelQuest::TLevelQuest(uint id_, bool active_, Importance importance_) :
	id(id), 
	active(active),
	importance(importance)
{		
	string raw_taskID = *LevelQuestsController::getInfo().getParameter(id, "tasks").as<string>();
	raw_taskID = raw_taskID.substr(2, raw_taskID.size() - 2);
	std::vector<string> raw_taskIDs = String::split(raw_taskID, ',');
	std::vector<uint> taskIDs(raw_taskIDs.size());
	for(uint i = 0; i != raw_taskIDs.size(); ++i) {
		taskIDs[i] = std::stoi(raw_taskIDs[i]);
	}

	string raw_rewardID = *LevelQuestsController::getInfo().getParameter(id, "rewards").as<string>();
	raw_rewardID = raw_rewardID.substr(2, raw_rewardID.size() - 2);
	std::vector<string> raw_rewardIDs = String::split(raw_rewardID, ',');
	std::vector<uint> rewardIDs(raw_rewardIDs.size());
	for(uint i = 0; i != raw_rewardIDs.size(); ++i) {
		rewardIDs[i] = std::stoi(raw_rewardIDs[i]);
	}
	
	tasks = TQuestTasks(taskIDs);
	rewards = TQuestRewards(rewardIDs);
}
	
	
bool TLevelQuest::isCompleted() const {
	return tasks.isCompleted();
}	
bool TLevelQuest::isFailed() const {
	return tasks.isFailed();
}	
bool TLevelQuest::isActive() const {
	return active;
}	
	
void TLevelQuest::setCompleted(bool value) {
	tasks.setCompleted(value);
}	
void TLevelQuest::setFailed(bool value) {
	tasks.setFailed(value);
}	
void TLevelQuest::setActive(bool value) {
	active = value;
}	
void TLevelQuest::setImportance(Importance value) {
#if _DEBUG_
	if ((value < QuestImportance::_min) || (QuestImportance::_max < value)) {
		throw_("Unable to set quest importance: unexpected value.", "TLevelQuest::setImportance");
	}
#endif
	importance = value;
}	
	
const std::vector<TQuestTask>& TLevelQuest::getProgress() const {
	return tasks.getProgress();
}	
TLevelQuest::ClassId TLevelQuest::getID() const {
	return id;
}	
const string& TLevelQuest::getDescription() const {
	return *LevelQuestsController::getInfo().getParameter(id, "description").as<string>();
}	
const string& TLevelQuest::getTitle() const {
	return *LevelQuestsController::getInfo().getParameter(id, "name").as<string>();
}	
const string& TLevelQuest::getRewardDescription() const {
	return reward.getDescription();
}	
TLevelQuest::Importance TLevelQuest::getImportance() const {
	return importance;
}	
	
void TLevelQuest::update() {
	if (isActive() == false) {
		return;
	}
		
	tasks.update();
	if (tasks.isCompleted() == true) {
		reward.grant();
		setActive(false);
	}
}
