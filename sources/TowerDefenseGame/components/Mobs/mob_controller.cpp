#include "mob_controller.h"


bool MobController::isAnyMobsOnTile(const Point2ui& tilePos, int appearance = MobAppearance::Ground) {
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TMob> m = dynamic_cast<TMob*>((*it).get());
		if (m == nullptr) { continue; }

		if (m->isOnTile(tilePos, appearance) == true) { return true; }
	}
	return false;
}
	
void MobController::updatePathes() {
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TMob> m = dynamic_cast<TMob*>((*it).get());
		if (m == nullptr) { continue; }
				
		m->checkPath();
	}
}

TMobsInfo::TMobInfo::Value& MobController::getParameter(TMob::ClassId classId, const string& key) {
	return LevelHelper::getLevelInstance().getInfo().getGameObjectsInfo().getMobsInfo().getParameter(classId, key);
}

const TSceneResources& MobController::getResources() {
	return LevelHelper::getLevelInstance().getScene().getResources();
}
	
const TPassabilityMap& MobController::getPassabilityMap() {
	return getNodeMap().getPassabilityMap();
}
	
const TNodeMap& MobController::getNodeMap() {
	return getLevel().getScene().getMap().getNodeMap();
}
	
TMobsFactory& MobController::getMobFactory() {
	return getLevel().getInfo().getGameObjectsInfo().getMobsInfo().getFactory();
}

float MobController::getCurrentHealth(TMob::ClassId classId) {
	return *getParameter(classId, "health").as<float>();
}
	
int MobController::getCurrentReward(TMob::ClassId classId) {
	return *getParameter(classId, "reward").as<int>();		
}
	
float MobController::getCurrentSpeed(TMob::ClassId classId) {
	return *getParameter(classId, "speed").as<float>();
}
	
float MobController::getCurrentPoints(TMob::ClassId classId) {
	/* used reward as base */
	return getCurrentReward(classId) * GameMechanics::MOB_POINTS_PER_HEALTH;
}

int MobController::getPathSelectionPolicy() {
	switch (LevelHelper::getLevelInstance().getCode().getType()) {
	case LevelCodeType::Free: { return PathSelectionPolicy::Dynamic; }
	case LevelCodeType::Company: { return PathSelectionPolicy::Static; }
	default: { return PathSelectionPolicy::Undefined; }
	}
}

TLevel& MobController::getLevel() {
	return LevelHelper::getLevelInstance();
}

TScene::Objects MobController::getSceneObjects() {
	return LevelHelper::getLevelInstance().getScene().getObjects();
}
