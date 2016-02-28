#ifndef __LEVELSTAGE_H__
#define __LEVELSTAGE_H__

#include "..\..\Core\core.h"
#include "..\Info\stageinfo.h"

class TB_Castle;
class TLevel;

/*
	Contains Stage parameters, object references and preferences.
*/
class TLevelStage
{
public:
	TLevelStage();	
	~TLevelStage();

	/*
		Modifies level data by 'source' data
	*/
	void load(const TStageInfo& source, TLevel* level);
	
	void setNumber(ushort value);
	void setRunning(bool value);
		
	uint getTimer() const;
	ushort getNumber() const;
	TB_Castle const* getCastle() const;
	float getCastleHealth() const;
	
	void update();

	bool isCastleAlive() const;
	bool isRunning() const;
	bool isCastleRepairable() const;
private:
	ushort number;
	
	//Castle parameters:
	TB_Castle* castle;
	
	//Progress:
	uint time;
	bool running;
};

#endif
