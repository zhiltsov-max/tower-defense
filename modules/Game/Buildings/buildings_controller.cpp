#include "buildings_controller.h"



namespace TD {


const TBuildingRegistry& TBuildingsController::GetRegistry() const {
    return registry;
}

TBuildingRegistry& TBuildingsController::GetRegistry() {
    return registry;
}


} // namespace TD


/*
void BuildingsController::removeNonBuilt() {
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TBuilding> b = dynamic_cast<TBuilding*>((*it).get());
		if (b == nullptr) { continue; }

		if (b->isBuilt() == false) {
			b->rejectBuilding();
		}
	}
}
	
void BuildingsController::setSelectionOfAll(bool value) {
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TBuilding> b = dynamic_cast<TBuilding*>((*it).get());
		if (b == nullptr) { continue; }

		b->setSelection(value);
	}
}
	
bool BuildingsController::isAllPlaced() {
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TBuilding> b = dynamic_cast<TBuilding*>((*it).get());
		if (b == nullptr) { continue; }

		if (b->isBuilt() == false) { 
			return false;
		}
	}
	return true;
}

std::list<std::shared_ptr<TBuilding>>&& BuildingsController::getSelectedBuildings() {
	std::list<std::shared_ptr<TBuilding>> selectedBuildings;
				
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TBuilding> b = dynamic_cast<TBuilding*>((*it).get());
		if (b == nullptr) { continue; }

		if (b->isSelected() == true) {
			selectedBuildings.push_back(b);
		}
	}
		
	return std::move(selectedBuildings);
}

const TBuildingUpgrades& BuildingsController::getUpgrades() {

}
	
bool BuildingsController::isTileTaken(uint tileX, uint tileY) {
	const Point2f& pos(tileX, tileY);

	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TBuilding> b = dynamic_cast<TBuilding*>((*it).get());
		if (b == nullptr) { continue; }

		if (b->isOnTile(pos) == true) {
			return true;
		}
	}
	return false
}
	

bool BuildingsController::canBuildThere(const Point2f& where_, const Point2f& size) {
	for(uint xChk = std::floor(where_.x() - (size.x() * 0.5));
		xChk < std::ceil(where_.x() + (size.x() * 0.5)); ++xChk) {
			
		for(uint yChk = std::floor(where_.y() - (size.y() * 0.5));
			yChk < std::ceil(where_.y() + (size.y() * 0.5)); ++yChk) {
				
			if (isTileBuildable(xChk, yChk) == false) {
				return false;
			}
			if (MobsController::isAnyMobsOnTile(xChk, yChk, MobAppearance::Ground) == true) {
				return false;
			}
			if (isTileTaken(xChk, yChk) == true) {
				return false;
			}
		}
	}
	return true;
}
	
TBuildingsInfo::TBuildingInfo::Value& BuildingsController::getParameter(TBuilding::ClassId classId, const string& key) {
	return LevelHelper::getLevelInstance().getInfo().getBuildingParameter(classId, key);
}
	
const TSceneResources& BuildingsController::getResources() {
	return getLevel().getScene().getResources();
}
	
void BuildingsController::handleResearch(TResearch::ClassId id) {
    const TBuildingUpgrade& research = getUpgrades().[id];
	if (research.isResearched() == false) {
		return;
	}
		
	for(  building:TBuilding = EachIn TBuildingController.GetAllBuildings() ){
		building.updateParameters();
	}
}
	
bool BuildingsController::isBuildingResearched(TBuilding::ClassId classId) {
	return getParameter(classId, BuildingUpgradeModifier::Open).as<bool>();
}

void BuildingsController::explodeAround(const Point2ui& p1, const Point2ui& p2) {
	auto sceneObjects = getSceneObjects();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		std::shared_ptr<TBuilding> b = dynamic_cast<TBuilding*>((*it).get());
		if (b == nullptr) { continue; }

		if (b->absPos().isInRect(p1, p2) == true) {
			b->explode();
		}
	}
}

bool BuildingsController::isTileBuildable(uint posX, uint posY) {
	return getLevel().getScene().getMap().isTileBuildable(posX, posY);
}

TScene::Objects BuildingsController::getSceneObjects() {
	return LevelHelper::getLevelInstance().getScene().getObjects();
}
*/
