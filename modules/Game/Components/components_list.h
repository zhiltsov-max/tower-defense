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

static constexpr std::map<GE::ComponentIDs, GE::ComponentSystem>
_componentSystemForId = {
    {GE::ComponentIDs::PlayerStatistics, GE::ComponentSystem::data},
    {GE::ComponentIDs::PlayerProgress, GE::ComponentSystem::logics},
    {GE::ComponentIDs::PlayerQuests, GE::ComponentSystem::logics},
    {GE::ComponentIDs::PlayerResearches, GE::ComponentSystem::logics},
    {GE::ComponentIDs::PlayerCredits, GE::ComponentSystem::data},

    {GE::ComponentIDs::ResearchesTreeView, GE::ComponentSystem::ui},
    {GE::ComponentIDs::ResearchesTreeItemView, GE::ComponentSystem::ui},

    {GE::ComponentIDs::LevelTileMap, GE::ComponentSystem::data},
    {GE::ComponentIDs::LevelTileMapView, GE::ComponentSystem::graphics},
    {GE::ComponentIDs::LevelNodeMap, GE::ComponentSystem::data},
    {GE::ComponentIDs::LevelNodeMapView, GE::ComponentSystem::graphics}, //TODO: debug only?
    {GE::ComponentIDs::LevelPassabilityMap, GE::ComponentSystem::data},
    {GE::ComponentIDs::LevelPassabilityMapView, GE::ComponentSystem::graphics}, //TODO: debug only?

    {GE::ComponentIDs::LevelBuildingsController, GE::ComponentSystem::logics},
    {GE::ComponentIDs::LevelMobsController, GE::ComponentSystem::logics},
    {GE::ComponentIDs::LevelQuestsController, GE::ComponentSystem::logics},
    {GE::ComponentIDs::LevelResearchesController, GE::ComponentSystem::logics}
};
static constexpr GE::ComponentSystem
GetComponentSystemForID(const GE::ComponentIDs& id) {
    return _componentSystemForId[id];
}

} // namespace TD

#endif // COMPONENTS_LIST_H
