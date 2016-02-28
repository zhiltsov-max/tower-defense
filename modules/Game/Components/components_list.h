#ifndef COMPONENTS_LIST_H
#define COMPONENTS_LIST_H

#include "GameEngine/component.h"
#include "GameEngine/component_systems.h"



namespace TD {


enum class ComponentID : uint {
    PlayerStatistics,
    PlayerProgress,
    PlayerQuests,
    PlayerResearches,
    PlayerCredits,
    PlayerPoints,

    ResearchesTreeView,
    ResearchesTreeItemView
};


} // namespace TD

#endif // COMPONENTS_LIST_H
