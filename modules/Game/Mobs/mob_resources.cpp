#include "mob_resources.h"


std::vector<string> MobResources::get(const TNamedData<string>& source, const TMobsInfo& info) {
	std::vector<string> res;
		
	string raw_ids = source["id"];
	raw_ids = raw_ids.substr(2, raw_ids.size() - 2);
	std::vector<string> ids = String::split(raw_ids, ',');

	for(auto it = ids.cbegin(); it != ids.cend(); ++it) {
		uint classId = std::stoi(*it);
        string raw_resources = info.getParameter(classId, "resources");
		std::vector<string> parts = String::split(raw_resources, ';');
        res.insert(res.begin(), parts.cbegin(), parts.cend());
	}
		
    return res;
}
