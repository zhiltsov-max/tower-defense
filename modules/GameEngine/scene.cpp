#include "scene.h"
#include "game_engine.h"



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

TScene::Handle TScene::CreateComponent(const TComponent::ID& id,
    const ComponentSystem& componentClass, const TComponentCreateArgs* args)
{
#if defined(_DEBUG)
    ASSERT(engine != nullptr, "Game engine must be set.")
#else
    if (engine == nullptr) {
        return Handle::Undefined;
    }
#endif // DEBUG

    auto* system = engine->GetComponentSystems().
        systems[(uchar)componentClass];

    Handle handle(system->CreateComponent(id, args), componentClass);
    return handle;
}

void TScene::RemoveComponent(const Handle& handle) {
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

TComponent* TScene::GetComponent(const TScene::Handle& handle) {
    return engine->GetComponentSystems().
        systems[(uchar)handle.GetSystem()]->GetComponent(handle);
}
