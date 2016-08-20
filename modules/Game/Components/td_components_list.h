#ifndef TD_COMPONENTS_LIST_H
#define TD_COMPONENTS_LIST_H

#include "GameEngine/component.h"
#include "GameEngine/component_system_type.h"


enum class GE::ComponentIDs : GE::TComponentID {
    Position2d = 0,
    Animation,

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

#define TD_DECLARE_COMPONENT_CLASS(CLASS_NAME, COMPONENT_ID, SYSTEM_ID) \
    namespace TD { \
    class CLASS_NAME; \
    }; \
    namespace GE { \
    template<> \
    struct ComponentID< ::TD::CLASS_NAME > \
    { \
        inline static constexpr ComponentIDs value() { return COMPONENT_ID; } \
    }; \
    template<> \
    struct ComponentClass< ::TD::CLASS_NAME > \
    { \
        inline static constexpr ComponentSystem value() { return SYSTEM_ID; } \
    }; \
    }

#endif // TD_COMPONENTS_LIST_H
