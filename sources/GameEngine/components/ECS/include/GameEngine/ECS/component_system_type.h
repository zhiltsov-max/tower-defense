#ifndef COMPONENT_SYSTEM_TYPE_H
#define COMPONENT_SYSTEM_TYPE_H

#include "GameEngine/Utility/core.h"


namespace GE {

template<class Component>
struct ComponentClass;

using TComponentSystemTypeId = uchar;
enum class ComponentSystem : TComponentSystemTypeId;

} // namespace GE

#endif // COMPONENT_SYSTEM_TYPE_H
