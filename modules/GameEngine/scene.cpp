#include "scene.h"
#include "GameEngine/game_engine.h"


namespace GE {

const TScene::Resources& TScene::GetResources() const {
    return resources;
}

TScene::Resources& TScene::GetResources() {
    return resources;
}

const TScene::SceneObjects& TScene::GetObjects() const {
    return sceneObjects;
}

TScene::SceneObjects& TScene::GetObjects() {
    return sceneObjects;
}

void TScene::SetGameEngine(TGameEngine* instance) {
    engine = instance;
}

TScene::ComponentHandle TScene::CreateComponent(const TComponent::ID& id,
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
        systems[(uchar)componentClass];

    ComponentHandle handle(system->CreateComponent(id, args), componentClass);
    return handle;
}

void TScene::RemoveComponent(const ComponentHandle& handle) {
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

TComponent* TScene::GetComponent(const TScene::ComponentHandle& handle) {
    return engine->GetComponentSystems().
        systems[(uchar)handle.GetSystem()]->GetComponent(handle);
}

} //namespace GE
