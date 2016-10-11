#include "GameEngine/scene_component_manager.h"
#include "GameEngine/game_engine.h"


namespace GE {

TSceneComponentManager::TSceneComponentManager() :
    engine(nullptr),
    sceneObjectManager(nullptr),
    componentBindingsTable(0, hashComponentHandle)
{}

void TSceneComponentManager::SetGameEngine(TGameEngine* instance) {
    engine = instance;
}

void TSceneComponentManager::SetSceneObjectManager(
    TSceneObjectManager* instance)
{
    sceneObjectManager = instance;
}

bool TSceneComponentManager::IsEmpty() const {
    ASSERT(engine != nullptr, "Game engine must be set.");

    const auto& systems = engine->GetComponentSystemsManager().GetSystems();
    for (const auto& system : systems) {
        if (system.second->IsEmpty() == false) {
            return false;
        }
    }
    return true;
}

void TSceneComponentManager::Clear() {
    ASSERT(engine != nullptr, "Game engine must be set.");

    for (auto& system : engine->GetComponentSystemsManager().GetSystems()) {
        system.second->Clear();
    }

    if (sceneObjectManager != nullptr) {
        for (auto& entry : componentBindingsTable) {
            if (sceneObjectManager->HasObject(entry.second.first) == false) {
                continue;
            }

            auto& object = (*sceneObjectManager)[entry.second.first];
            if (object.HasComponent(entry.second.second) == true) {
                object.RemoveComponent(entry.second.second);
            }
        }
    }
    componentBindingsTable.clear();
}

void TSceneComponentManager::BindComponent(
    const ComponentHandle& componentHandle,
    const ComponentPath& componentPath)
{
    ASSERT((IsComponentBound(componentHandle) == false) ||
        ((IsComponentBound(componentHandle) == true) &&
        (componentBindingsTable[componentHandle].first.IsNull() == true)),
        "Component is already bound.")
    componentBindingsTable[componentHandle] = componentPath;
}

void TSceneComponentManager::UnbindComponent(
    const ComponentHandle& componentHandle)
{
    componentBindingsTable.erase(componentHandle);
}

bool TSceneComponentManager::IsComponentBound(
    const ComponentHandle& componentHandle)
{
    return (componentBindingsTable.count(componentHandle) != 0) &&
        (componentBindingsTable[componentHandle].first.IsNull() == false);
}

const TSceneComponentManager::ComponentPath&
TSceneComponentManager::GetComponentBinding(
    const ComponentHandle& componentHandle) const
{
    return componentBindingsTable.at(componentHandle);
}

TSceneComponentManager::ComponentPath
TSceneComponentManager::GetComponentBinding(
    const ComponentHandle& componentHandle)
{
    return componentBindingsTable.at(componentHandle);
}

TSceneComponentManager::EntriesConstRange
TSceneComponentManager::EnumerateEntries() const {
    return {componentBindingsTable.begin(), componentBindingsTable.end()};
}

TSceneComponentManager::EntriesRange
TSceneComponentManager::EnumerateEntries() {
    return {componentBindingsTable.begin(), componentBindingsTable.end()};
}

size_t TSceneComponentManager::hashComponentHandle(
    const ComponentHandle& handle)
{
    return handle.GetValue();
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
    BindComponent(handle, ComponentPath(
        SceneObjectHandle::Undefined, TSceneObject::HandleUndefined));

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

    if (handle.IsNull() == true) {
        return;
    }
    auto* system = engine->GetComponentSystemsManager().
        FindSystem(handle.GetSystem());
    ASSERT(system != nullptr, "Unexpected system requested for component.");

    system->RemoveComponent(handle);
    engine->GetMessageSystem().Unsubscribe(handle);
    engine->GetMessageSystem().UnsubscribeFrom(handle);
    UnbindComponent(handle);
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

} // namespace GE
