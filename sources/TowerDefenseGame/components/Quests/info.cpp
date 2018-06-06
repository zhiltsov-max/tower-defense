#include "info.h"


const string dataAddress = "Data/Quests/QuestInfo.dat";

TQuestsInfo::TQuestsInfo() 
{
	std::ifstream* stream = new std::ifstream(dataAddress);
	if (stream == nullptr) {
		throw_("File '" + dataAddress + "' was not found.", "TQuestsInfo::TQuestsInfo");
	}

	uint lastQuestId;

	std::set<string> requestedTasks;
	std::set<string> requestedRewards;

	while (stream->good()) {
		string str; std::getline(*stream, str);
		if (String::startsWith(str, "'") == true) { continue; }
		if (String::left(str, 1) != "#") { continue; }

		lastQuestId = std::stoi(str.substr(1, str.size() - 1));
		if (lastQuestId == 0) {
			throw_("Failed to load quest parameters: Unexpected questId '" + str.substr(1, str.size() - 1) + "'.", "TQuestsInfo::TQuestsInfo");
		}
	
		Info& lastQuest = data[lastQuestId];
		Info::Loader loader;
		loader.load(&lastQuest, *stream);

		const auto reqTask = TQuestTasksInfo::getRequested(*lastQuest["tasks"].as<string>());
		requestedTasks.insert(reqTask.cbegin(), reqTask.cend());

		const auto reqRew = TQuestRewardsInfo::getRequested(*lastQuest["rewards"].as<string>());
		requestedRewards.insert(reqRew.cbegin(), reqRew.cend());
	}
	stream->close();

	tasks = TQuestTasksInfo(requestedTasks);
	rewards = TQuestRewardsInfo(requestedRewards);
}

TQuestsInfo::~TQuestsInfo() 
{}

const string& TQuestsInfo::getParameter(uint questId, const string& key) const {
	return data.at(questId).at(key);
}	
const TQuestRewardsInfo& TQuestsInfo::getRewards() const {
	return rewards;
}	
const TQuestTasksInfo& TQuestsInfo::getTasks() const {
	return tasks;
}



void TLevelQuest::Info::Loader::load(TLevelQuest::Info* info, std::istream& source) const {
	if (info == nullptr) {
		throw_("Storage is null.", "TLevelQuest::Info::Loader::load");
	}

	string buffer;

	std::getline(source, buffer);
	(*info)["name"].as<string>() = new string(buffer);

	std::getline(source, buffer);
	(*info)["desciption"].as<string>() = new string(buffer);

	std::getline(source, buffer);
	(*info)["tasks"].as<string>() = new string(buffer);
	
	std::getline(source, buffer);
	(*info)["rewards"].as<string>() = new string(buffer);
}
