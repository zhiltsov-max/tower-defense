#ifndef LEVEL_RESEARCHES_H
#define LEVEL_RESEARCHES_H

#include "../../Info/level_info.h"
#include "upgradestree.h"

class TLevelResearches
{
public:
	TLevelResearches(const TLevelInfo& levelInfo, const TLevel* level) :
		upgradesTree(levelInfo, level)
	{ /*TO DO: */ }
	
	const TBuildingUpgrades& getTree() const {
		return upgradesTree;
	}
	TBuildingUpgrades& getTree() {
		return upgradesTree;
	}
	
	void setTree(const TBuildingUpgrades& value) {
        upgradesTree = value;
    }

private:
	TBuildingUpgrades upgradesTree;
};

#endif //LEVEL_RESEARCHES_H
