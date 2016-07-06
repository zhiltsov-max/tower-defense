#ifndef COMPONENTS_LIST_H
#define COMPONENTS_LIST_H

#include "GameEngine/component.h"
#include "GameEngine/component_systems.h"


enum class GE::ComponentIDs : GE::TComponentID {
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

namespace TD {

static constexpr GE::ComponentSystem
GetComponentSystemForID(const GE::ComponentIDs& id);

} // namespace TD

#endif // COMPONENTS_LIST_H
