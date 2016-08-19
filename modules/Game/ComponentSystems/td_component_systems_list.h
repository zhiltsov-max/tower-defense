#ifndef TD_COMPONENT_SYSTEMS_LIST_H
#define TD_COMPONENT_SYSTEMS_LIST_H

#include "GameEngine/component_system_type.h"


enum class GE::ComponentSystem : GE::TComponentSystemTypeId {
    _min = 0,

    Movement = 0,
    Logics,
    UI,
    Graphics,
    Sound,

    _count,
    _undefined = _count
};

#endif // TD_COMPONENT_SYSTEMS_LIST_H
