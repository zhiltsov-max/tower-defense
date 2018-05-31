#ifndef COMPONENT_REGISTRY_H
#define COMPONENT_REGISTRY_H

#include "GameEngine/component.h"
#include "GameEngine/component_system_type.h"
#include "GameEngine/registry.h"


namespace GE {

struct TComponentCreateArgs
{
    virtual ~TComponentCreateArgs() = default;
};

using TComponentCreate =
    std::unique_ptr<TComponent> (*)(const TComponentCreateArgs*);

struct TComponentRegistryEntry
{
    ComponentSystem system;
    TComponentCreate create;
};

using TComponentRegistry = TRegistry<TComponentRegistryEntry, TComponent::ID>;

} // namespace GE

#endif // COMPONENT_REGISTRY_H
