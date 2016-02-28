#include "triggers.h"
#include "controller.h"
#include <ios>


TQuestTriggers::TQuestTriggers(const std::vector<uint>& ids) :
	data()
{
	for(auto it = ids.cbegin(); it != ids.cend(); ++it) {
		uint classId = std::stoi(getTriggersInfo().getParameter(*it, "classId"));

		const string& args_raw = getTriggersInfo().getParameter(*it, "args");			
		TNamedData<string> args;
		if (args_raw.empty() == false) {
			std::istream* is = new std::istringstream(args_raw);
			args = ParseData(is);			
			delete is;
		}	

		data.push_back(Trigger(getFactory().create(classId, args)));
	}
}	
	
void TQuestTriggers::update() {
	for(auto it = data.begin(); it != data.end(); ++it) {
		(*it)->update();
	}
}

static const TQuestTriggerFactory& getFactory() {
	return getTriggersInfo().getFactory();
}
static const TQuestTriggersInfo& getTriggersInfo() {
	return LevelQuestsController::getTasksInfo().getTriggersInfo();
}