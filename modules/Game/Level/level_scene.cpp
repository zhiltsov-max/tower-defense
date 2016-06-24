#include "level_scene.h"


namespace TD {

TLevelScene::TLevelScene(const TLevelInfoScene& info, GE::GameEngine& engine) :
    scene()
{
    scene.SetGameEngine(&engine);
    loadResources(info);
    loadObjects(info);
}

TLevelScene::ComponentHandle
TLevelScene::CreateComponent(const GE::TComponent::ID& id,
    const GE::TComponentCreateArgs* args)
{
    return scene.CreateComponent(id, ComponentSystemForId[id], args);
}

void TLevelScene::RemoveComponent(const ComponentHandle& handle) {
    return scene.RemoveComponent(handle);
}

GE::TComponent* TLevelScene::GetComponent(const ComponentHandle& handle) {
    return scene.GetComponent(handle);
}

const TLevelScene::Object&
TLevelScene::FindObject(const ObjectName& name) const {
    return scene.GetObjects()[name];
}

TLevelScene::Object&
TLevelScene::FindObject(const ObjectName& name) {
    return scene.GetObjects()[name];
}

const TLevelScene::Object&
TLevelScene::FindObject(const ObjectHandle& handle) const {
    return scene.GetObjects()[handle];
}

TLevelScene::Object& TLevelScene::FindObject(const ObjectHandle& handle) {
    return scene.GetObjects()[handle];
}

bool TLevelScene::HasObject(const ObjectName& name) const {
    return scene.GetObjects().HasObject(name);
}

bool TLevelScene::HasObject(const ObjectHandle& handle) const {
    return scene.GetObjects().HasObject(handle);
}

TLevelScene::ObjectHandle TLevelScene::GetHandle(const ObjectName& name) const {
    return scene.GetObjects().GetHandle(name);
}

TLevelScene::ObjectHandle
TLevelScene::AddSceneObject(const ObjectName& name, const Object& sceneObject) {
    return scene.GetObjects().AddSceneObject(name, sceneObject);
}

TLevelScene::Object TLevelScene::RemoveSceneObject(const ObjectName& name) {
    return scene.GetObjects().RemoveSceneObject(name);
}

TLevelScene::Object TLevelScene::RemoveSceneObject(const ObjectHandle& handle) {
    return scene.GetObjects().RemoveSceneObject(handle);
}

void TLevelScene::Clear() {
    scene.GetObjects().Clear();
}

bool TLevelScene::IsEmpty() const {
    return scene.GetObjects().IsEmpty();
}

TLevelScene::ObjectHandle
TLevelScene::AddSceneObject(const ObjectName& name, SceneObject&& sceneObject) {
    return scene.GetObjects().AddSceneObject(name, std::move(sceneObject));
}

void TLevelScene::loadResources(const TLevelInfoScene& info) {
    for (const auto& entry : info.resources.data) {
        scene.GetResources().LoadResource(entry);
    }
}

void TLevelScene::loadObjects(const TLevelInfoScene& info) {
    for (const auto& objectInfo : info.objects) {
        Object object;
        for (const auto& componentInfo : objectInfo.components) {
            const auto componentHandle = CreateComponent(componentInfo.id,
                ComponentSystemForId[componentInfo.id],
                componentInfo.parameters);
            object.AddComponent(componentInfo.name, componentHandle);
        }
        AddSceneObject(objectInfo.name, object);
    }
}

} // namespace TD
