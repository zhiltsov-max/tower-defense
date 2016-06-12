#ifndef LEVEL_DATA_GAME_OBJECTS_H
#define LEVEL_DATA_GAME_OBJECTS_H

#include "level_info_game_objects.h"
#include "Game/Quests/quests_controller.h"
#include "Game/Researches/researches_controller.h"
#include "Game/Buildings/buildings_controller.h"
#include "Game/Mobs/mobs_controller.h"
#include "Game/Map/level_map.h"



namespace TD {


struct TLevelSceneDataGameObjects
{
    using Buildings = TBuildingsController;
    Buildings buildings;

    using Mobs = TMobsController;
    Mobs mobs;

    using Quests = TQuestsController;
    Quests quests;

    using Researches = TResearchesController;
    Researches researches;

    using Map = TLevelMap;
    Map map;


    TLevelSceneDataGameObjects(const TLevelInfoGameObjects& info);
};


} // namespace TD

#endif // LEVEL_DATA_GAME_OBJECTS_H
