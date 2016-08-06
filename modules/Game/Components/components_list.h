#ifndef COMPONENTS_LIST_H
#define COMPONENTS_LIST_H

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

namespace TD {

namespace CS {

namespace impl {

GE::TComponentRegistry& GetComponentsRegistry();

} // namespace impl

template<class C>
void RegisterComponentClass() {
    GE::TComponentRegistry::Entry entry;
    entry.create = &C::Create;
    entry.system = GE::ComponentClass<C>::value;
    impl::GetComponentsRegistry().Register(GE::ComponentID<C>::value, entry);
}

const GE::TComponentRegistry& GetComponentsRegistry();

} // namespace CS

} // namespace TD

#endif // COMPONENTS_LIST_H
