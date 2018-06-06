#include "helper.h"

void LevelHelper::setLevelInstance(TLevel* instance) {
	level = instance;
}

TLevel& LevelHelper::getLevelInstance() {
	return *level;
}
		
void LevelHelper::pause() {
	level->setGameSpeed(GameSpeed::Pause);
}
	
void LevelHelper::increaseSpeed() {
	level->setGameSpeed(level->getGameSpeed() + 1);
}
	
LevelHelper::repairBase(uchar percent = 100) {
	if (100 < percent) {
#if _DEBUG_
		throw_("Unexpected percent to repair: " + std::to_string(percent), "LevelHelper::repairBase");
#else
		percent = std::min(100, percent);
#endif
	}

	TB_Castle& castle = level->getStage().getCastle();
	if (isCastleRepairable() == false) {
		return;
	}

	uint deficit = castle.getMaxHealth() - castle.getHealth();
	uint canRepair = std::min((uint)level->getProgress().getCredits() / GameMechanics::CREDITS_PER_CASTLE_HP, percent);
	uint toRepair = std::min(canRepair, deficit);
		
	if (toRepair == 0) {
		return;
	}
		
	castle.repair(toRepair);
		
	ushort cost = toRepair * GameMechanics::CREDITS_PER_CASTLE_HP;
	level->getProgress().setCredits(level->getProgress().getCredits() - cost);
}

bool LevelHelper::isCastleRepairable() {
    return level->getInfo().getGameObjectsInfo().getBuildingInfo().isCastleRepairable();
}
