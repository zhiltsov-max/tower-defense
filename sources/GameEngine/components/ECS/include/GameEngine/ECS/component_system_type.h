#ifndef COMPONENT_SYSTEM_TYPE_H
#define COMPONENT_SYSTEM_TYPE_H

#include "GameEngine/utility.h"


GE_BEGIN_ENGINE_NAMESPACE

template<class Component>
struct ComponentClass;

using TComponentSystemTypeId = uchar;
enum class ComponentSystem : TComponentSystemTypeId;

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_SYSTEM_TYPE_H
