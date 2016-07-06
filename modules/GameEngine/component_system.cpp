#include "component_system.h"
#include "GameEngine/component.h"
#include "GameEngine/game_engine.h"


namespace GE {

const TComponentSystem::Handle TComponentSystem::HandleUndefined = -1u;

TComponentSystem::Handle TComponentSystem::CreateComponent(
    const TComponent::ID& typeID, const TComponentCreateArgs* args)
{
    ASSERT(componentRegistry != nullptr, "Component registry is not set.");
    ASSERT(componentRegistry->IsRegistered(typeID) == true, "Unknown type id.");

    auto& create = (*componentRegistry)[typeID];
    PComponent ptr = std::move(create(args));
    auto* component = ptr.get();
    components.emplace_back(std::move(ptr));
    auto handle = components.size() - 1;
    const auto messagesList = component->GetAcceptedMessages();
    Subscribe(handle, messagesList.begin(), messagesList.end());

    return handle;
}

void TComponentSystem::RemoveComponent(const Handle& handle) {
    auto* component = GetComponent(handle);
    const auto messagesList = component->GetAcceptedMessages();
    Unsubscribe(handle, messagesList.begin(), messagesList.end());

    auto it = components.begin();
    std::advance(it, handle);
    components.erase(it);
}

TComponentSystem::Component*
TComponentSystem::GetComponent(const Handle& handle) {
    ASSERT(handle < components.size(), "Wrong component handle.");

    return components[handle].get();
}

void TComponentSystem::Subscribe(const Handle& handle, const Message::ID& id) {
    ASSERT(handle < components.size(), "Wrong component handle.");

    listeners[id].push_back(handle);
}

void
TComponentSystem::Unsubscribe(const Handle& handle, const Message::ID& id) {
    ASSERT(handle < components.size(), "Wrong component handle.");

    auto currentListeners = listeners.find(id);
    if (currentListeners == listeners.end()) {
        return;
    }

    for (auto it = currentListeners->second.begin(),
        iend = currentListeners->second.end(); it != iend; ++ it)
    {
        if (*it == handle) {
            it = currentListeners->second.erase(it);
        }
    }
}

void TComponentSystem::HandleMessage(const Message& message, Context& context) {
    if (listeners.count(message.GetID()) == 0) {
        return;
    }

    for (auto& handle : listeners.at(message.GetID())) {
        GetComponent(handle)->HandleMessage(message, context);
    }
}

void TComponentSystem::SetComponentRegistry(TComponentRegistry* instance) {
    componentRegistry = instance;
}

} //namespace GE
