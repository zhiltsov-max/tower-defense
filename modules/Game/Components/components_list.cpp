#include "Game/Components/components_list.h"

#include "Game/Map/level_node_map.h"
#include "Game/Map/level_passability_map.h"
#include "Game/Map/level_tile_map.h"

#include "Game/Player/player_credits.h"


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

GE::ComponentSystem TD::GetComponentSystemForID(const GE::ComponentIDs& id) {
    return _componentSystemForId[id];
}
