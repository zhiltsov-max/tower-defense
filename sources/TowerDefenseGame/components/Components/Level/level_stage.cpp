#include "stage.h"
#include "..\Buildings\tb_castle.h"
#include "..\Info\stageinfo.h"


TLevelStage::TLevelStage() :
	number(0),
	running(false),
	castle(nullptr)
{}
	
TLevelStage::~TLevelStage() 
{}

/*
	Modifies level data by 'source' data
*/
void TLevelStage::load(const TStageInfo& source, TLevel* level) {
	if ((source.empty() == true) || (level == nullptr)) {
		return;
	}

	if (source.contains(StageInfo::Category_Value[StageInfo::Category_Entry::Map]) == true) {
		level->getScene().getMap().updateData(source.slice(StageInfo::Category_Value[StageInfo::Category_Entry::Map]));
	}
		
	if (source.contains(StageInfo::Category_Value[StageInfo::Category_Entry::Scripts]) == true) {
		level->getScene().getScripts().updateData(source.slice(StageInfo::Category_Value[StageInfo::Category_Entry::Scripts]));
		level->getScene().getScripts().runScript(StageScript::OnStageInit + "_" + number);
	}
		
	auto sceneObjects = level->getScene().getObjects();
	for(auto it = sceneObjects.cbegin(); it != sceneObjects.cend(); ++it) {
		TB_Castle* c = dynamic_cast<TB_Castle*>((*it).get());
		if (c != nullptr) {
			castle = c;
			break;
		}
	}
}
	
void TLevelStage::setNumber(ushort value) {
	number = value;
}	
void TLevelStage::setRunning(bool value) {
	running = value;
}
		
uint TLevelStage::getTimer() const {
	return time;
}
ushort TLevelStage::getNumber() const {
	return number;
}
TB_Castle const* TLevelStage::getCastle() const {
	return castle;
}	
float TLevelStage::getCastleHealth() const {
	if (castle == nullptr) { return 0.0f; }
	return castle->getHealth() * 100.0f / castle->getMaxHealth();
}
	
void TLevelStage::update() {
	++time;
}
		
bool TLevelStage::isCastleAlive() const {
	return castle->isAlive();
}
bool TLevelStage::isRunning() const {
	return running;
}
bool TLevelStage::isCastleRepairable() const {
	return castle->isRepairable();
}