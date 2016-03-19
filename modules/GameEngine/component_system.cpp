#include "component_system.h"



void TComponentSystem::Update(const TTime& step) {
    for (auto& component : components) {
        component->Update();
    }
}

const TComponentSystem::Handle TComponentSystem::CreateComponent(
    const TComponent::ID& typeID,
    const TComponentCreateArgs* args)
{
    ASSERT(componentRegistry != nullptr,
        "Component registry is not set.")

    ASSERT(componentRegistry->IsRegistered(typeID) == true,
        "Unknown type id.")

    auto& create = (*componentRegistry)[typeID];
    PComponent obj = std::move(create(args));
    components.emplace_back(std::move(obj));
    obj->Subscribe(*this);

    return Handle(components.size() - 1);
}

void TComponentSystem::RemoveComponent(const Handle& componentHandle) {
    auto* component = GetComponent(componentHandle);
    component->Unsubscribe(*this);

    auto it = components.begin();
    std::advance(it, componentHandle);
    components.erase(it);
}

TComponentSystem::Component* TComponentSystem::GetComponent(const Handle& handle) {
    ASSERT(handle < components.size(), "Wrong component handle.")

    return components[handle].get();
}

void TComponentSystem::SetRegistry(TComponentRegistry* instance) {
    componentRegistry = instance;
}


void TComponentSystem::Subscribe(Component* component,
    const Message::ID& id)
{
    ASSERT(component != nullptr, "Unexpected component")

    listeners[id].push_back(component);
}

void TComponentSystem::Unsubscribe(Component* component,
    const Message::ID& id)
{
    listeners[id].remove(component);
}

void TComponentSystem::HandleMessage(const Message& message) {
    if (listeners.count(message.GetID()) == 0) {
        return;
    }

    for (auto& listener : listeners[ message.GetID() ]) {
        listener->HandleMessage(message);
    }
}

