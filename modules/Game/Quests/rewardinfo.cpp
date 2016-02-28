#include "rewardinfo.h"
#include "..\..\..\Application\application.h"


const string dataAddress = "Data/Quests/RewardsInfo.dat";


std::vector<string>&& TQuestRewardsInfo::getRequested(const string& source) {
	const string source = source.substr(2, source.size() - 2);
	return std::move(String::split(source, ','));
}

TQuestRewardsInfo::TQuestRewardsInfo(const std::set<string>& requested) {
	std::ifstream* stream = new std::ifstream(dataAddress);
		
	uint lastRewardId;
		
	while (stream->good()) {
		string str; std::getline(*stream, str);
		if (String::startsWith(str, "'") == true) { continue; }
		if (String::left(str, 1) != "#") { continue; }
			
		lastRewardId = std::stoi(str.substr(1, str.size() - 1));
		if (requested.count(str.substr(1, str.size() - 1)) == 0) {
			continue;
		}
		
		Info& lastReward = data[lastRewardId];
		const Info::Loader loader;
		loader.load(&lastReward, *stream);
	}
		
	stream->close();
}

const TQuestRewardsInfo::Value& TQuestRewardsInfo::getParameter(TQuestReward::ClassId rewardId, const string& key) const {
    return data.at(rewardId).at(key);
}


TQuestReward::Info::Info() :
	parent_type()
{}

TQuestReward::Info::~Info()
{}




TQuestReward::Info::Loader::Loader() :
	parent_type()
{}

TQuestReward::Info::Loader::~Loader()
{}

void TQuestReward::Info::Loader::load(TQuestReward::Info* info, std::istream& source) const {
	if (info == nullptr) {
		throw_("Storage is null.", "TQuestReward::Info::Loader::load");
	}

	string buffer;

	std::getline(source, buffer);
	(*info)["desciption"].as<string>() = new string(buffer);

	std::getline(source, buffer);
	(*info)["type"].as<uint>() = new uint(std::stoul(buffer));

	std::getline(source, buffer);
	(*info)["reward"].as<string>() = new string(buffer);
}
