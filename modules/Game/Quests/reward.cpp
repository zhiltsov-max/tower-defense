#include "reward.h"
#include "controller.h"
#include "rewardimpl.h"
#include "rewardinfo.h"


TQuestReward::TQuestReward() 
{}

TQuestReward::TQuestReward(uint id_) :
	id(id_)
{
	typeID = *LevelQuestsController::getRewardsInfo().getParameter(id, "type").as<uint>();
}
		
uint TQuestReward::getID() const {
	return id;
}	
uint TQuestReward::getTypeID() const {
	return typeID;
}	
const string& TQuestReward::getDescription() const {
	return *LevelQuestsController::getRewardsInfo().getParameter(getID(), "description").as<string>();
}
	
void TQuestReward::grant() const {
	Impl::invoke(this);
}
	
std::vector<string>&& TQuestReward::getArgs() const {
	string raw_args = *LevelQuestsController::getRewardsInfo().getParameter(getID(), "reward").as<string>();
	raw_args = raw_args.substr(2, raw_args.size() - 2);
	return String::split(raw_args, ',');
}