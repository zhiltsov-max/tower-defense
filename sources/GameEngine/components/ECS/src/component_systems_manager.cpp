#include "GameEngine/ECS/component_systems_manager.h"


GE_BEGIN_ENGINE_NAMESPACE

const TComponentHandle TComponentHandle::Undefined{};

TComponentHandle::TComponentHandle() :
    value(TComponentSystem::HandleUndefined),
    system()
{}

TComponentHandle::TComponentHandle(const Handle& handle,
    const ComponentSystem& system
) :
    value(handle),
    system(system)
{}

const ComponentSystem& TComponentHandle::GetSystem() const {
    return system;
}

const TComponentSystem::Handle&
TComponentHandle::GetValue() const {
    return value;
}

bool TComponentHandle::operator == (
    const TComponentHandle& other) const
{
    return (system == other.system) &&
        (value == other.value);
}

bool TComponentHandle::operator != (const TComponentHandle& other) const
{
    return !operator==(other);
}

bool TComponentHandle::IsNull() const {
    return operator==(Undefined);
}

TComponentHandle::operator size_t() const {
    return value;
}


void TComponentSystemsManager::Update(const TTime& step, Context& context) {
    for (auto& system : systems) {
        system.second->Update(step, context);
    }
}

TComponentSystem*
TComponentSystemsManager::AddSystem(const ID& id, PSystem&& system) {
    ASSERT(HasSystem(id) == false, "System already exists");
    auto* ptr = system.get();
    if (system != nullptr) {
        system->SetComponentRegistry(&componentRegistry);
        systems.emplace(id, std::move(system));
    }
    return ptr;
}

bool TComponentSystemsManager::HasSystem(const ID& id) const {
    return nullptr != FindSystem(id);
}

void TComponentSystemsManager::RemoveSystem(const ID& id) {
    ASSERT(HasSystem(id) == true, "System does not exist");
    systems.erase(id);
}

const TComponentSystem* TComponentSystemsManager::FindSystem(const ID& id) const {
    const auto it = systems.find(id);
    if (it != systems.cend()) {
        return (*it).second.get();
    } else {
        return nullptr;
    }
}

TComponentSystem* TComponentSystemsManager::FindSystem(const ID& id) {
    const auto it = systems.find(id);
    if (it != systems.end()) {
        return (*it).second.get();
    } else {
        return nullptr;
    }
}

void TComponentSystemsManager::SendMessage(const Message& message,
    Context& context, const ComponentHandle& sender)
{
    for (auto& system : systems) {
        system.second->HandleMessage(message, sender, context);
    }
}

const TComponentSystemsManager::ComponentRegistry&
TComponentSystemsManager::GetComponentRegistry() const {
    return componentRegistry;
}

TComponentSystemsManager::ComponentRegistry&
TComponentSystemsManager::GetComponentRegistry() {
    return componentRegistry;
}

const TComponentSystemsManager::Systems&
TComponentSystemsManager::GetSystems() const {
    return systems;
}

TComponentSystemsManager::Systems& TComponentSystemsManager::GetSystems() {
    return systems;
}

GE_END_ENGINE_NAMESPACE
