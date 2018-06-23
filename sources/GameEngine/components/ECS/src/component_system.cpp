#include "component_system.h"
#include "GameEngine/ECS/component_registry.h"
#include "GameEngine/ECS/game_engine.h"


GE_BEGIN_ENGINE_NAMESPACE

const TComponentSystem::Handle TComponentSystem::HandleUndefined = -1u;

TComponentSystem::TComponentSystem() :
    componentRegistry(nullptr),
    components()
{}

TComponentSystem::Handle TComponentSystem::CreateComponent(
    const TComponent::ID& typeID, const TComponentCreateArgs* args)
{
    ASSERT(componentRegistry != nullptr, "Component registry is not set.");
    ASSERT(componentRegistry->IsRegistered(typeID) == true, "Unknown type id.");

    auto& create = (*componentRegistry)[typeID].create;
    PComponent ptr = std::move(create(args));
    components.emplace_back(std::move(ptr));
    return components.size() - 1;
}

bool TComponentSystem::HasComponent(const Handle& handle) const {
    return (handle < components.size()) && (components[handle] != nullptr);
}

void TComponentSystem::RemoveComponent(const Handle& handle) {
    if (HasComponent(handle) == false) {
        return;
    }

    auto it = components.begin();
    std::advance(it, handle);
    components.erase(it);
}

const TComponentSystem::Component*
TComponentSystem::GetComponent(const Handle& handle) const {
    if (HasComponent(handle) == true) {
        return components[handle].get();
    } else {
        return nullptr;
    }
}

TComponentSystem::Component*
TComponentSystem::GetComponent(const Handle& handle) {
    if (HasComponent(handle) == true) {
        return components[handle].get();
    } else {
        return nullptr;
    }
}

bool TComponentSystem::IsEmpty() const {
    return components.empty();
}

void TComponentSystem::Clear() {
    components.clear();
}

void TComponentSystem::SetComponentRegistry(TComponentRegistry* instance) {
    componentRegistry = instance;
}

GE_END_ENGINE_NAMESPACE
