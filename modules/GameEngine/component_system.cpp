#include "component_system.h"



void TComponentSystem::Update(const TTime& step) {
    for (auto& component : components) {
        component->Update();
    }
}

const Handle& TComponentSystem::CreateComponent(
    const TComponent::ID& typeID,
    const TComponentCreateArgs* args)
{
#if defined(_DEBUG)
    ASSERT(componentRegistry != nullptr,
        "Component registry is not set.")
#else //_DEBUG
    if (componentRegistry == nullptr) {
        return nullptr;
    }
#endif //_DEBUG

    if (componentRegistry->IsRegistered(typeID) == false) {
#if defined(_DEBUG)
        THROW("Unknown type id.")
#else
        return nullptr;
#endif
    }

    auto& create = (*componentRegistry)[typeID];
    PComponent obj = std::move(create(args));
    components.emplace_back(std::move(obj));
    obj->Subscribe(this);

    return Handle(components.size() - 1);
}

void TComponentSystem::RemoveComponent(const Handle& componentHandle) {
    auto* component = GetComponent(componentHandle);
    component->Unsubscribe(this);

    auto it = components.begin();
    std::advance(it, componentHandle);
    components.erase(it);
}

TComponentSystem::Component* TComponentSystem::GetComponent(const Handle& handle) {
#if defined(_DEBUG)
    ASSERT(handle < components.size(), "Wrong component handle.")
#else
    if (components.size() <= handle) {
        return nullptr;
    }
#endif // DEBUG
    return components[handle].get();
}

void TComponentSystem::SetRegistry(TComponentRegistry* instance) {
    componentRegistry = instance;
}


void TComponentSystem::Subscribe(Component* component,
    const Message::ID& id)
{
#if defined(_DEBUG)
    ASSERT(component != nullptr, "Unexpected component")
#else //_DEBUG
    if (component == nullptr) {
        return;
    }
#endif //_DEBUG

    listeners[id].push_back(component);
}

void TComponentSystem::Unsubscribe(Component* component,
    const Message::ID& id)
{
    listeners[id].erase(component);
}

void TComponentSystem::HandleMessage(const Message& message) {
    if (listeners.count(message.GetID()) == 0) {
        return;
    }

    for (auto& listener : listeners[ message.GetID() ]) {
        listener->HandleMessage(message);
    }
}

