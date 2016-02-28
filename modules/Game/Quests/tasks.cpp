#include "tasks.h"


TQuestTasks::TQuestTasks()
{}
TQuestTasks::TQuestTasks(const std::vector<TQuestTask::ClassId> &ids) :
{
	tasks = Data(ids.size());
	for(size_t i = 0; i != ids.size(); ++i) {
		data[i] = TQuestTask(ids[i]);
	}
}
	
	
const std::vector<TQuestTask>& TQuestTasks::getProgress() const {
	return data;
}	

bool TQuestTasks::isCompleted() const {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		if ((*it).isCompleted() == false) {
			return false;
		}
	}
	return true;
}	
bool TQuestTasks::isFailed() const {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		if ((*it).isFailed() == true) {
			return true;
		}
	}
	return false;
}
		
void TQuestTasks::setCompleted(bool value) {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		(*it).setCompleted(value);
	}
}	
void TQuestTasks::setFailed(bool value) {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		(*it).setFailed(value);
	}
}	
	
void TQuestTasks::update() {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		(*it).update();
	}
}
