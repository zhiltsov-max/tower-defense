#include "component_system.h"
#include "GameEngine/component_registry.h"
#include "GameEngine/game_engine.h"


namespace GE {

const TComponentSystem::Handle TComponentSystem::HandleUndefined = -1u;

TComponentSystem::TComponentSystem() :
    componentRegistry(nullptr),
    components(),
    listeners()
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
    UnsubscribeFrom(handle);

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
    listeners.clear();
}

void TComponentSystem::Subscribe(const Handle& source, const Handle& listener) {
    ASSERT((source < components.size()) || (source == HandleUndefined),
        "Wrong component handle.");
    ASSERT(listener < components.size(),"Wrong component handle.");

    listeners[source].push_back(listener);
}

void
TComponentSystem::Unsubscribe(const Handle& source, const Handle& listener) {
    ASSERT((source < components.size()) || (source == HandleUndefined),
        "Wrong component handle.");
    ASSERT(listener < components.size(),"Wrong component handle.");

    auto it = listeners.find(source);
    if (it == listeners.end()) {
        return;
    }

    it->second.erase(
        std::remove(it->second.begin(), it->second.end(), listener),
        it->second.end());
    if (it->second.empty() == true) {
        listeners.erase(it);
    }
}

void
TComponentSystem::Unsubscribe(const Handle& listener) {
    ASSERT(listener < components.size(),"Wrong component handle.");

    for (auto it = listeners.begin(); it != listeners.end(); ++it) {
        it->second.erase(
            std::remove(it->second.begin(), it->second.end(), listener),
            it->second.end());
        if (it->second.empty() == true) {
            listeners.erase(it);
        }
    }
}

void
TComponentSystem::UnsubscribeFrom(const Handle& source) {
    ASSERT((source < components.size()) || (source == HandleUndefined),
        "Wrong component handle.");

    listeners.erase(source);
}

void TComponentSystem::HandleMessage(const Message& message, Context& context,
    const Handle& source)
{
    auto it = listeners.find(source);
    if (it == listeners.end()) {
        return;
    }

    for (auto& listener : it->second) {
        auto* component = GetComponent(listener);
        if (component != nullptr) {
            component->HandleMessage(message, context);
        }
    }
}

void TComponentSystem::SetComponentRegistry(TComponentRegistry* instance) {
    componentRegistry = instance;
}

} //namespace GE
