#ifndef LEVELHELPER_H
#define LEVELHELPER_H

#include "../../Core/core.h"

class TLevel;

class LevelHelper /*Abstract*/
{
public:
	static void setLevelInstance(TLevel* instance);
	static TLevel& getLevelInstance();
		
	static void pause();	
	static void increaseSpeed();	
    static repairBase(uchar percent = 100);
		
	static bool isCastleRepairable();

	LevelHelper() = delete;
private:
	static TLevel* level;
};

#endif
