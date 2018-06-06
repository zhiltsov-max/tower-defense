#include "taskinfo.h"


const string dataAddress = "Data/Quests/TasksInfo.dat";

std::vector<string>&& TQuestTasksInfo::getRequested(const string& source) {
	const string source = source.substr(2, source.size() - 2);
	return std::move(String::split(source, ','));
}
		
TQuestTasksInfo::TQuestTasksInfo(const std::set<string>& requested) {
	std::ifstream* stream = new std::ifstream(dataAddress);


	uint lastTaskId;
		
	std::set<string> requestedTriggers;
		
	while (stream->good()) {
		string str; std::getline(*stream, str);
		if (String::startsWith(str, "'") == true) { continue; }
		if (String::left(str, 1) != "#") { continue; }
			
		lastTaskId = std::stoi(str.substr(1, str.size() - 1));
		if (requested.count(str.substr(1, str.size() - 1)) == 0) {
			continue;
		}
		
		Info& lastTask = data[lastTaskId];

		Info::Loader loader;
		loader.load(&lastTask, *stream);

		const auto reqTask = TQuestTriggersInfo::getRequested(*lastTask["triggers"].as<string>());
		requestedTriggers.insert(reqTask.cbegin(), reqTask.cend());
	}
		
	stream->close();
		
	triggers = TQuestTriggersInfo(requestedTriggers);
}

const TQuestTasksInfo::Value& TQuestTasksInfo::getParameter(TQuestTask::ClassId taskId, const string& key) const {
	return data.at(taskId).at(key);
}	
const TQuestTriggersInfo& TQuestTasksInfo::getTriggers() const {
	return triggers;
}


TQuestTask::Info::Info() :
	parent_type()
{}

TQuestTask::Info::~Info()
{}




TQuestTask::Info::Loader::Loader() :
	parent_type()
{}

TQuestTask::Info::Loader::~Loader()
{}

void TQuestTask::Info::Loader::load(TQuestTask::Info* info, std::istream& source) const {
	if (info == nullptr) {
		throw_("Storage is null.", "TQuestTask::Info::Loader::load");
	}

	string buffer;

	std::getline(source, buffer);
	(*info)["desciption"].as<string>() = new string(buffer);

	std::getline(source, buffer);
	(*info)["total"].as<uint>() = new uint(std::stoul(buffer));
	
	std::getline(source, buffer);
	(*info)["triggers"].as<string>() = new string(buffer);
}
