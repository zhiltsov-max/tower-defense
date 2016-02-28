#ifndef GAME_OBJECTS_INFO_H
#define GAME_OBJECTS_INFO_H

#include "level_info_raw.h"
#include "level_info_mobs.h"
#include "level_info_buildings.h"
#include "level_info_researches.h"
#include "level_info_quests.h"



namespace TD {


namespace GameObjectsInfo {


static constexpr string Mobs = "mobs";
static constexpr string Buildings = "buildings";
static constexpr string Researches = "researches";
static constexpr string Quests = "quests";


} // namespace GameObjectsInfo


struct TLevelInfoGameObjects
{
	TMobsInfo mobs;
	TBuildingsInfo buildings;
    TResearchesInfo researches;
    TQuestsInfo quests;


    TLevelInfoGameObjects(const TRawLevelInfo& source) :
        mobs(source.slice(GameObjectsInfo::Mobs)),
        buildings(source.slice(GameObjectsInfo::Buildings)),
        researches(source.slice(GameObjectsInfo::Researches)),
        quests(source.slice(GameObjectsInfo::Quests))
    {}
};


} // namespace TD

#endif // GAME_OBJECTS_INFO_H
