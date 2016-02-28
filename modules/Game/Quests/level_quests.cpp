#include "quests.h"


TLevelQuests::TLevelQuests() :
	summaryState(QuestState::Normal)
{}	
	
void TLevelQuests::loadForStage(const TNamedData<string>& source) {
	for(auto it = data.begin(); it != data.end(); ++it) {
		if ((*it).second.isCompleted() == true) {
			(*it).second.setActive(false);
		}
	}
	
	if (source.empty() == true) {
		return;
	}
		
	for(auto it = source.cbegin(); it != source.cend(); ++it) {
		uint id = std::stoi((*it).first);
		if (id == 0) {
			continue;
		}
		const string value = (*it).second.substr(2, (*it).second.size() - 2);
		const std::vector<string> parts = String::split(value, partsSeparator);
						
		bool isMain = std::stoi(parts[0]);
		bool accepted = std::stoi(parts[1]);
		TLevelQuest quest = TLevelQuest(id, accepted);
		if (isMain == true) {
			quest.setImportance(QuestImportance::Main);
		} else {
			quest.setImportance(QuestImportance::Usual);
		}
		
		data[id] = quest;
	}
}
	
	
void TLevelQuests::setQuest(TLevelQuest::ClassId id, const TLevelQuest& value) {
	data[id] = value;
}
const TLevelQuest& TLevelQuests::getQuest(TLevelQuest::ClassId id) const {
	return data[id];
}
TLevelQuest& TLevelQuests::getQuest(TLevelQuest::ClassId id) {
	return data[id];
}
	
void TLevelQuests::setCompleted(bool value) {
	for(auto it = data.begin(); it != data.end(); ++it) {
		if ((*it).second.getImportance() == QuestImportance::Main) {
			(*it).second.setCompleted(value);
		}
	}
	if (value == true) {
		summaryState = QuestState::Completed;
	} else {
		summaryState = QuestState::Normal;
	}
}	
void TLevelQuests::setFailed(bool value) {
	for(auto it = data.begin(); it != data.end(); ++it) {
		if ((*it).second.getImportance() == QuestImportance::Main) {
			(*it).second.setFailed(value);
		}
	}
	if (value == true) {
		summaryState = QuestState::Failed;
	} else {
		summaryState = QuestState::Normal;
	}
}
		
bool TLevelQuests::isStageCompleted() const {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		if ((*it).second.getImportance() == QuestImportance::Main) {
			if ((*it).second.isCompleted() == false) {
				return false;
			}
		}
	}
	return true;
}
bool TLevelQuests::isStageFailed() const {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		if ((*it).second.getImportance() == QuestImportance::Main) {
			if ((*it).second.isFailed() == true) {
				return true;
			}
		}
	}
	return false;
}
	
bool TLevelQuests::isLevelCompleted() const {
	return summaryState == QuestState::Completed;
}	
bool TLevelQuests::isLevelFailed() const {
	return summaryState == QuestState::Failed;
}	
	
void TLevelQuests::update() {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		(*it).second.update();
	}
}
