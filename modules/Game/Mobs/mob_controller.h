#ifndef MOB_CONTROLLER_H
#define MOB_CONTROLLER_H

#include "mob.h"

/*TO DO: delete this shit and create normal class in component model
 *it have to implement mobs' lifecycle control
*/

class MobController /*Abstract*/
{
public:
	static bool isAnyMobsOnTile(const Point2ui& tilePos, int appearance = MobAppearance::Ground);
	
	static void updatePathes();

    static TMobsInfo::TMobInfo::Value& getParameter(TMob::ClassId classId, const string& key);

	static const TSceneResources& getResources();
	
	static const TPassabilityMap& getPassabilityMap();
	
	static const TNodeMap& getNodeMap();
	
	static TMobsFactory& getFactory();

    static float getCurrentHealth(TMob::ClassId classId);
	
    static int getCurrentReward(TMob::ClassId classId);
	
    static float getCurrentSpeed(TMob::ClassId classId);
	
    static float getCurrentPoints(TMob::ClassId classId);

	static int getPathSelectionPolicy();

    MobController() = delete;
private:
	static TLevel& getLevel();

	static TScene::Objects getSceneObjects();
};

#endif //MOB_CONTROLLER_H
