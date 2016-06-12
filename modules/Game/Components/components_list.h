#ifndef COMPONENTS_LIST_H
#define COMPONENTS_LIST_H

#include "GameEngine/component.h"
#include "GameEngine/component_systems.h"


enum class GE::ComponentIDs : uint {
    PlayerStatistics,
    PlayerProgress,
    PlayerQuests,
    PlayerResearches,
    PlayerCredits,
    PlayerPoints,

    ResearchesTreeView,
    ResearchesTreeItemView,

    LevelTileMap,
    LevelTileMapView,
    LevelNodeMap,
    LevelNodeMapView, //TODO: debug only?
    LevelPassabilityMap,
    LevelPassabilityMapView, //TODO: debug only?
};

#endif // COMPONENTS_LIST_H
