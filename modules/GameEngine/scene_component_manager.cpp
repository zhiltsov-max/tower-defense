#include "GameEngine/scene_component_manager.h"
#include "GameEngine/game_engine.h"


namespace GE {

void TSceneComponentManager::SetGameEngine(TGameEngine* instance) {
    engine = instance;
}

bool TSceneComponentManager::IsEmpty() const {
    ASSERT(engine != nullptr, "Game engine must be set.");

    for (const auto& system : engine->GetComponentSystemsManager().GetSystems()) {
        if (system.second->IsEmpty() == false) {
            return false;
        }
    }
    return true;
}

void TSceneComponentManager::Clear() {
    ASSERT(engine != nullptr, "Game engine must be set.");

    for (const auto& system : engine->GetComponentSystemsManager().GetSystems()) {
        system.second->Clear();
    }
}

TSceneComponentManager::ComponentHandle
TSceneComponentManager::CreateComponent(const TComponent::ID& id,
    const TComponentCreateArgs* args)
{
    ASSERT(engine != nullptr, "Game engine must be set.");

    const auto& componentClass = engine->GetComponentSystemsManager().
        GetComponentRegistry()[id].system;
    auto* system = engine->GetComponentSystemsManager().
        FindSystem(componentClass);
    ASSERT(system != nullptr, "Unexpected system requested for component.");

    ComponentHandle handle(system->CreateComponent(id, args), componentClass);
    return handle;
}

bool TSceneComponentManager::HasComponent(const ComponentHandle& handle) const {
    ASSERT(engine != nullptr, "Game engine must be set.");

    const auto* system = engine->GetComponentSystemsManager().
        FindSystem(handle.GetSystem());
    if (system != nullptr) {
        return system->HasComponent(handle);
    } else {
        return false;
    }
}

void TSceneComponentManager::RemoveComponent(const ComponentHandle& handle) {
    ASSERT(engine != nullptr, "Game engine must be set.");

    auto* system = engine->GetComponentSystemsManager().
        FindSystem(handle.GetSystem());
    ASSERT(system != nullptr, "Unexpected system requested for component.");

    system->RemoveComponent(handle);
}

const TComponent*
TSceneComponentManager::GetComponent(const ComponentHandle& handle) const {
    ASSERT(engine != nullptr, "Game engine must be set.");

    const auto* system = engine->GetComponentSystemsManager().
        FindSystem(handle.GetSystem());
    if (system != nullptr) {
        return system->GetComponent(handle);
    } else {
        return nullptr;
    }
}

TComponent*
TSceneComponentManager::GetComponent(const ComponentHandle& handle) {
    ASSERT(engine != nullptr, "Game engine must be set.");

    auto* system = engine->GetComponentSystemsManager().
        FindSystem(handle.GetSystem());
    if (system != nullptr) {
        return system->GetComponent(handle);
    } else {
        return nullptr;
    }
}

} //namespace GE
