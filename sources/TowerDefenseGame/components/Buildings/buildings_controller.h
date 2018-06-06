#ifndef BUILDINGS_CONTROLLER_H
#define BUILDINGS_CONTROLLER_H

#include "buildings_info.h"



namespace TD {


class TBuildingsController
{
public:
    using Registry = TBuildingsRegistry;


    TBuildings GetAllBuildings() const;

    const Registry& GetRegistry() const;
    Registry& GetRegistry();

private:
    Registry registry;
};


} // namespace TD



//class BuildingsController /*Abstract*/
/*{
public:	
	static void removeNonBuilt();
	
	static void setSelectionOfAll(bool value);
	
	static bool isAllPlaced();

	static std::list<std::shared_ptr<TBuilding>>&& getSelectedBuildings();

	static const TBuildingUpgrades& getUpgrades();
	
	static bool isTileTaken(uint tileX, uint tileY);
/*
	/*
        Check if building could be built there.
    *//*
	static bool canBuildThere(const Point2f& tilePos, const Point2f& tileSize);
	
    static TBuildingsInfo::TBuildingInfo::Value& getParameter(TBuilding::ClassId classId, const string& key);
	
	static const TSceneResources& getResources();
	
    static void handleResearch(TResearch::ClassId id);
	
    static bool isBuildingResearched(TBuilding::ClassId classId);

	static void explodeAround(const Point2ui& p1, const Point2ui& p2);

	BuildingsController() = delete;
private:
	static bool isTileBuildable(uint posX, uint posY);

	static TScene::Objects getSceneObjects();
};*/


#endif //BUILDINGS_CONTROLLER_H
