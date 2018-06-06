#include "triggerinfo.h"


const string dataAddress = "Data/Quests/TriggersInfo.dat";

std::vector<string>&& TQuestTriggersInfo::getRequested(const string& source) {
	const string source = source.substr(2, source.size() - 2);
	return std::move(String::split(source, ','));
}

TQuestTriggersInfo::TQuestTriggersInfo(const std::set<string>& requested) {
	std::ifstream* stream = new std::ifstream(dataAddress);
	
	uint lastTriggerId;
		
	std::set<string> requestedTriggers;
		
	while (stream->good()) {
		string str; std::getline(*stream, str);
		if (String::startsWith(str, "'") == true) { continue; }
		if (String::left(str, 1) != "#") { continue; }
			
		lastTriggerId = std::stoi(str.substr(1, str.size() - 1));
		if (requested.count(str.substr(1, str.size() - 1)) == 0) {
			continue;
		}
			
		Info lastTrigger = data[lastTriggerId];
		Info::Loader loader;
		loader.load(&lastTrigger, *stream);
	}
		
	stream->close();
}

const string& TQuestTriggersInfo::getParameter(uint triggerId, const string& key) const {
    return data.at(triggerId).at(key);
}
	
const TQuestTriggerFactory& TQuestTriggersInfo::getFactory() const {
	return questTriggerFactory;
}



TQuestTrigger::Info::Info() :
	parent_type()
{}

TQuestTrigger::Info::~Info()
{}




TQuestTrigger::Info::Loader::Loader() :
	parent_type()
{}

TQuestTrigger::Info::Loader::~Loader()
{}

void TQuestTrigger::Info::Loader::load(TQuestTrigger::Info* info, std::istream& source) const {
	if (info == nullptr) {
		throw_("Storage is null.", "TQuestTrigger::Info::Loader::load");
	}

	string buffer;

	std::getline(source, buffer);
	(*info)["classId"].as<uint>() = new uint(std::stoul(buffer));
	
	std::getline(source, buffer);
	(*info)["args"].as<string>() = new string(buffer);
}
