#ifndef TD_COMPONENT_SYSTEMS_LIST_H
#define TD_COMPONENT_SYSTEMS_LIST_H

#include "GameEngine/component_systems.h"


enum class GE::ComponentSystem : GE::TComponentSystemTypeId {
    _min = 0,

    input = 0,
    data,
    movement,
    logics,
    ui,
    graphics,
    sound,

    _count,
    _undefined = _count
};

#endif // TD_COMPONENT_SYSTEMS_LIST_H
