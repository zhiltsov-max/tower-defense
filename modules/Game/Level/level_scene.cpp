#include "level_scene.h"
#include "Game/Components/components_list.h"


namespace TD {

TLevelScene::TLevelScene(const Parameters& info, GE::GameEngine* engine) :
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
    return scene.CreateComponent(id, GetComponentSystemForId(id), args);
}

void TLevelScene::RemoveComponent(const ComponentHandle& handle) {
    return scene.RemoveComponent(handle);
}

const TComponent* TLevelScene::FindComponent(const ComponentPath& path) const {
    return scene.FindComponent(path);
}

TComponent* TLevelScene::FindComponent(const ComponentPath& path) {
    return scene.FindComponent(path);
}

GE::TComponent* TLevelScene::GetComponent(const ComponentHandle& handle) {
    return scene.GetComponent(handle);
}

const TLevelScene::Object*
TLevelScene::FindSceneObject(const ObjectName& name) const {
    return scene.FindSceneObject(name);
}

TLevelScene::Object*
TLevelScene::FindSceneObject(const ObjectName& name) {
    return scene.FindSceneObject(name);
}

const TLevelScene::Object&
TLevelScene::GetSceneObject(const ObjectHandle& handle) const {
    return scene.GetSceneObject(handle);
}

TLevelScene::Object& TLevelScene::FindObject(const ObjectHandle& handle) {
    return scene.GetSceneObject(handle);
}

bool TLevelScene::HasObject(const ObjectName& name) const {
    return scene.HasObject(name);
}

bool TLevelScene::HasObject(const ObjectHandle& handle) const {
    return scene.HasObject(handle);
}

TLevelScene::ObjectHandle TLevelScene::GetHandle(const ObjectName& name) const {
    return scene.GetHandle(name);
}

TLevelScene::ObjectHandle
TLevelScene::AddSceneObject(const ObjectName& name, const Object& sceneObject) {
    return scene.AddSceneObject(name, sceneObject);
}

TLevelScene::Object TLevelScene::RemoveSceneObject(const ObjectName& name) {
    return scene.RemoveSceneObject(name);
}

TLevelScene::Object TLevelScene::RemoveSceneObject(const ObjectHandle& handle) {
    return scene.RemoveSceneObject(handle);
}

void TLevelScene::Clear() {
    scene.Clear();
}

bool TLevelScene::IsEmpty() const {
    return scene.IsEmpty();
}

void TLevelScene::Update(const GE::TTime& step) {
    GE::TGameEngine::Context context(gameEngine, this);
    gameEngine->Update(step, context);
}

void TLevelScene::SetGameEngine(GE::TGameEngine* instance) {
    gameEngine = instance;
    scene.SetGameEngine(instance);
}

TLevelScene::ObjectHandle
TLevelScene::AddSceneObject(const ObjectName& name, SceneObject&& sceneObject) {
    return scene.AddSceneObject(name, std::move(sceneObject));
}

void TLevelScene::loadResources(const Parameters& info) {
    for (const auto& entry : info.resources.data) {
        scene.GetResources().LoadResource(entry);
    }
}

void TLevelScene::loadObjects(const Parameters& info) {
    for (const auto& objectInfo : info.objects) {
        Object object;
        for (const auto& componentInfo : objectInfo.components) {
            const auto componentHandle = CreateComponent(componentInfo.id,
                componentInfo.parameters);
            object.AddComponent(componentInfo.name, componentHandle);
        }
        AddSceneObject(objectInfo.name, object);
    }
}

} // namespace TD
