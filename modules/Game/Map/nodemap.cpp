#include "nodemap.h"
#include "../../../Application/application.h"


TNodeMap::TNodeMap(const TNamedData<string>& source)
{
    loadData(source);
}

void TNodeMap::updateData(const TNamedData<string>& source) {
	if (source.empty() == true) {
		return;
	}		
	loadData(source);
}	
	
TNodeMap::Path& TNodeMap::addPath(uint x, uint y) {
    pathes.emplace_back();
    pathes.back().emplace_back(x, y);
	return pathes.back();
}

TPathNode& TNodeMap::addEnter(uint x, uint y) {
	for(auto it = enters.cbegin(); it != enters.cend(); ++it) {
		if ( (*it).getPos() != Point2ui(x, y) ) {
#if _DEBUG_
            Throw("Failed to add new NodeMap enter: enter already exists." + string((*it).getPos()), "TNodeMap::addEnter");
#endif
			return;
		}
	}
    enters.emplace_back(x, y);
}
	
TPathNode& TNodeMap::addExit(uint x, uint y) {
	for(auto it = exits.cbegin(); it != exits.cend(); ++it) {
		if ( (*it).getPos() != Point2ui(x, y) ) {
#if _DEBUG_
            Throw("Failed to add new NodeMap exit: exit already exists." + string((*it).getPos()), "TNodeMap::addExit");
#endif
			return;
		}
	}
    exits.emplace_back(x, y);
}	
	
const TPathNode& TNodeMap::getEnter(size_t index = 0) const {
	return enters[index];
}

TPathNode& TNodeMap::getEnter(size_t index = 0) {
	return enters[index];
}

const TPathNode& TNodeMap::getExit(size_t index) const {
	return exits[index];
}

TPathNode& TNodeMap::getExit(size_t index) {
	return exits[index];
}
	
const TNodeMap::Path& TNodeMap::getPath(size_t index) const {
	return pathes[index];
}

TNodeMap::Path& TNodeMap::getPath(size_t index) {
	return pathes[index];
}

size_t TNodeMap::getPathCount() const {
	return pathes.size();
}	

size_t TNodeMap::getEnterCount() const {
	return enters.size();
}

size_t TNodeMap::getExitCount() const {
	return exits.size();
}	
	
const TPathNode& TNodeMap::findNearestExit(uint x, uint y) const {
    auto minNode = exits.cbegin();
	double minSq = std::pow((double)x - (*minNode).getPos().x(), 2) + std::pow((double)x - (*minNode).getPos().y(), 2); 

	for(auto node = minNode + 1; node != exits.cend(); ++node) { 
        const double curDist = std::pow((double)x - (*node).getPos().x(), 2) + std::pow((double)y - (*node).getPos().y(), 2);
		if (curDist < minSq) {
			minNode = node;
			minSq = curDist;
		}
	}
    return *minNode;
}
		
bool TNodeMap::isExit(const TPathNode& node) const {
	for(auto it = exits.cbegin(); it != exits.cend(); ++it) {
        if (*it == node) {
			return true; 
		}
	}
	return false;
}
bool TNodeMap::isEnter(const TPathNode& node) const {
	for(auto it = enters.cbegin(); it != enters.cend(); ++it) {
        if (*it == node) {
			return true; 
		}
	}
	return false;
}

void TNodeMap::loadData(const TNamedData<string>& source) {
	if (source.empty() == true) {
        Throw("Failed to load NodeMap: source is empty.", "TNodeMap::loadData");
	}

	loadEnters(source.slice("enters"));
	loadExits(source.slice("exits"));
	loadPathes(source.slice("pathes"));
}	

void TNodeMap::loadPathes(const TNamedData<string>& source) {
	if (source.empty() == true) {
		return;
	}
		
	if (source.contains("count") == false) {
        Throw("Failed to load NodeMap: unknown count of pathes.", "TNodeMap::loadPathes");
	}
	int pathCount = std::stoi(source["count"]);
		
	for(int id = 0; id != pathCount; ++id) {
		Path path;
				
		const int enterId = std::stoi(source["enter"]);
		path->push_back(enters[enterId]);
			
		const size_t pathLength = std::stoi(source[std::to_string((long long)id) + source.keySep() + "count"]);
		for(size_t index = 0; index != pathLength; ++index) {
			string raw_node = source[std::to_string((long long)id) + source.keySep() + std::to_string((long long)index)];
			raw_node = raw_node.substr(2, raw_node.size() - 2);
			std::vector<string> parts = String::split(raw_node, ',');
			path->push_back(TPathNode(
				std::stoi(parts[0]), 
				std::stoi(parts[1]))
				);
		}
			
		int exitId = std::stoi(source["exit"]);
		path->push_back(exits[exitId]);
			
		pathes.push_back(path);
	}
}

void TNodeMap::loadEnters(const TNamedData<string>& source) {
	if (source.empty() == true) {
		return;
	}
	
	const size_t count = std::stoi(source["count"]);
	for(size_t id = 0; id != count; ++id) {
		string raw_node = source[std::to_string((long long)id)];
		raw_node = raw_node.substr(2, raw_node.size() - 2);
		std::vector<string> parts = String::split(raw_node, ',');
		addEnter(std::stoi(parts[0]), std::stoi(parts[1]));
	}
}

void TNodeMap::loadExits(const TNamedData<string>& source) {
	if (source.empty() == true) {
		return;
	}
	
	const size_t count = std::stoi(source["count"]);
	for(size_t id = 0; id != count; ++id) {
		string raw_node = source[std::to_string((long long)id)];
		raw_node = raw_node.substr(2, raw_node.size() - 2);
		std::vector<string> parts = String::split(raw_node, ',');
		addExit(std::stoi(parts[0]), std::stoi(parts[1]));
	}				
}
