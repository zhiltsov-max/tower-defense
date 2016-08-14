#ifndef TD_COMPONENTS_LIST_H
#define TD_COMPONENTS_LIST_H

#include "GameEngine/component.h"
#include "GameEngine/component_systems.h"


enum class GE::ComponentIDs : GE::TComponentID {
    Position2d = 0,

    Health,

    PlayerStatistics,
    PlayerProgress,
    PlayerQuests,
    PlayerResearches,
    PlayerCredits,

    ResearchesTreeView,
    ResearchesTreeItemView,

    LevelTileMap,
    LevelTileMapView,
    LevelNodeMap,
    LevelNodeMapView, //TODO: debug only?
    LevelPassabilityMap,
    LevelPassabilityMapView, //TODO: debug only?

    LevelBuildingsController,
    LevelMobsController,
    LevelQuestsController,
    LevelResearchesController,

    _count
};

#endif // TD_COMPONENTS_LIST_H
