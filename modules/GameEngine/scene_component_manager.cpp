#include "scene_component_manager.h"
#include "GameEngine/game_engine.h"


namespace GE {

void TSceneComponentManager::SetGameEngine(TGameEngine* instance) {
    engine = instance;
}

TSceneComponentManager::ComponentHandle
TSceneComponentManager::CreateComponent(const TComponent::ID& id,
    const ComponentSystem& componentClass, const TComponentCreateArgs* args)
{
#if defined(_DEBUG)
    ASSERT(engine != nullptr, "Game engine must be set.")
#else
    if (engine == nullptr) {
        return ComponentHandle::Undefined;
    }
#endif // DEBUG

    auto* system = engine->GetComponentSystems().
        systems[static_cast<uchar>(componentClass)];

    ComponentHandle handle(system->CreateComponent(id, args), componentClass);
    return handle;
}

void TSceneComponentManager::RemoveComponent(const ComponentHandle& handle) {
#if defined(_DEBUG)
    ASSERT(engine != nullptr, "Game engine must be set.")
#else
    if (engine == nullptr) {
        return;
    }
#endif // DEBUG

    const auto& componentClass = handle.GetSystem();
    auto* system = engine->GetComponentSystems().systems[(uchar)componentClass];
    system->RemoveComponent(handle);
}

TComponent* TSceneComponentManager::GetComponent(
    const TSceneComponentManager::ComponentHandle& handle)
{
    return engine->GetComponentSystems().
        systems[static_cast<uchar>(handle.GetSystem())]->GetComponent(handle);
}

} //namespace GE
