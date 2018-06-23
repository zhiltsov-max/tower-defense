#ifndef COMPONENT_REGISTRY_H
#define COMPONENT_REGISTRY_H

#include "GameEngine/ECS/component.h"
#include "GameEngine/ECS/component_system_type.h"
#include "GameEngine/ECS/registry.h"


GE_BEGIN_ENGINE_NAMESPACE

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

GE_END_ENGINE_NAMESPACE

#endif // COMPONENT_REGISTRY_H
