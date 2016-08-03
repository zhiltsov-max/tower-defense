#include "level_scene.h"
#include "GameEngine/game_engine_context.h"


namespace TD {

TLevelScene::TLevelScene(const Parameters& info, GE::TGameEngine* engine) :
    scene()
{
    SetGameEngine(engine);
    loadResources(info);
    loadObjects(info);
}

TLevelScene::ComponentHandle
TLevelScene::CreateComponent(const GE::TComponent::ID& id,
    const GE::TComponentCreateArgs* args)
{
    return scene.CreateComponent(id, args);
}

void TLevelScene::RemoveComponent(const ComponentHandle& handle) {
    return scene.RemoveComponent(handle);
}

TLevelScene::ComponentHandle
TLevelScene::FindComponent(const ComponentPath& path) const {
    return scene.FindComponent(path);
}

bool TLevelScene::HasComponent(const ComponentPath& path) const {
    return scene.HasComponent(path);
}

bool TLevelScene::HasComponent(const ComponentHandle& handle) const {
    return scene.HasComponent(handle);
}

const GE::TComponent*
TLevelScene::GetComponent(const ComponentHandle& handle) const {
    return scene.GetComponent(handle);
}

GE::TComponent* TLevelScene::GetComponent(const ComponentHandle& handle) {
    return scene.GetComponent(handle);
}

TLevelScene::ObjectHandle
TLevelScene::FindSceneObject(const ObjectName& name) const {
    return scene.FindSceneObject(name);
}

const TLevelScene::Object&
TLevelScene::GetSceneObject(const ObjectHandle& handle) const {
    return scene.GetSceneObject(handle);
}

TLevelScene::Object& TLevelScene::GetSceneObject(const ObjectHandle& handle) {
    return scene.GetSceneObject(handle);
}

bool TLevelScene::HasObject(const ObjectName& name) const {
    return scene.HasObject(name);
}

bool TLevelScene::HasObject(const ObjectHandle& handle) const {
    return scene.HasObject(handle);
}

TLevelScene::ObjectHandle
TLevelScene::AddSceneObject(const ObjectName& name, const Object& sceneObject) {
    return scene.AddSceneObject(name, sceneObject);
}

void TLevelScene::RemoveSceneObject(const ObjectName& name) {
    scene.RemoveSceneObject(name);
}

void TLevelScene::RemoveSceneObject(const ObjectHandle& handle) {
    scene.RemoveSceneObject(handle);
}

void TLevelScene::Clear() {
    scene.Clear();
}

bool TLevelScene::IsEmpty() const {
    return scene.IsEmpty();
}

void TLevelScene::Update(const GE::TTime& step) {
    GE::TGameEngine::Context context(gameEngine, &scene);
    gameEngine->Update(step, context);
}

void TLevelScene::SetGameEngine(GE::TGameEngine* instance) {
    gameEngine = instance;
    scene.SetGameEngine(instance);
}

TLevelScene::ObjectHandle
TLevelScene::AddSceneObject(const ObjectName& name, Object&& sceneObject) {
    return scene.AddSceneObject(name, std::move(sceneObject));
}

void TLevelScene::loadResources(const Parameters& info) {
    for (const auto& entry : info.resources) {
        //TODO:
        //scene.GetResourceManager().LoadResource(entry, GE::SceneResourceTypeID::);
    }
}

void TLevelScene::loadObjects(const Parameters& info) {
    for (const auto& objectInfo : info.objects) {
        Object object;
        for (const auto& componentInfo : objectInfo.components) {
            const auto componentHandle = CreateComponent(componentInfo.id,
                componentInfo.parameters.get());
            object.AddComponent(componentInfo.name, componentHandle);
        }
        AddSceneObject(objectInfo.name, object);
    }
}

} // namespace TD
