#ifndef COMPONENT_SYSTEMS_ENUM_H
#define COMPONENT_SYSTEMS_ENUM_H

#include "Core/core.h"


namespace GE {

using TComponentSystemTypeId = uchar;
enum class ComponentSystem : TComponentSystemTypeId {
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

} // namespace GE

#endif // COMPONENT_SYSTEMS_ENUM_H
