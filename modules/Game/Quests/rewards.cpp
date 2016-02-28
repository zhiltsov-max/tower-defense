#include "rewards.h"
#include "..\..\..\Core\core.h"


TQuestRewards::TQuestRewards(const std::vector<ClassId>& ids)
{
	data.resize(ids.size());
	for(size_t i = 0; i != ids.size(); ++i) {
		data[i] = TQuestReward(ids[i]);
	}
}
	
std::vector<string>&& TQuestRewards::getDescription() const {
	std::vector<string> res(data.size());
	for(size_t i = 0; i != data.size(); ++i) {
		res[i] = data[i].getDescription();
	}
	return std::move(res);
}

void TQuestRewards::grant() const {
	for(auto it = data.cbegin(); it != data.cend(); ++it) {
		(*it).grant();
	}
}
