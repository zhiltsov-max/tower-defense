#include "scene.h"
#include "GameEngine/game_engine.h"


namespace GE {

TScene::ComponentHandle
TScene::CreateComponent(const TComponent::ID& id,
    const TComponentCreateArgs* args)
{
    return componentManager.CreateComponent(id, args);
}

void TScene::RemoveComponent(const ComponentHandle& handle) {
    return componentManager.RemoveComponent(handle);
}

TScene::ComponentHandle TScene::FindComponent(const ComponentPath& path) const {
    if (objectManager.HasObject(path.first) == true) {
        const auto& object = objectManager[path.first];
        if (object.HasComponent(path.second) == true) {
            return object[path.second];
        }
    }
    return ComponentHandle::Undefined;
}

bool TScene::HasComponent(const ComponentPath& path) const {
    return FindComponent(path) != ComponentHandle::Undefined;
}

bool TScene::HasComponent(const ComponentHandle& handle) const {
    return componentManager.HasComponent(handle);
}

const TComponent* TScene::GetComponent(const ComponentHandle& handle) const {
    return componentManager.GetComponent(handle);
}

TComponent* TScene::GetComponent(const ComponentHandle& handle) {
    return componentManager.GetComponent(handle);
}

TScene::ObjectHandle TScene::FindSceneObject(const ObjectName& name) const {
    return objectManager.GetHandle(name);
}

const TScene::Object& TScene::GetSceneObject(const ObjectHandle& handle) const {
    return objectManager[handle];
}

TScene::Object& TScene::GetSceneObject(const ObjectHandle& handle) {
    return objectManager[handle];
}

bool TScene::HasObject(const ObjectName& name) const {
    return objectManager.HasObject(name);
}

bool TScene::HasObject(const ObjectHandle& handle) const {
    return objectManager.HasObject(handle);
}

TScene::ObjectHandle
TScene::AddSceneObject(const ObjectName& name, const Object& sceneObject) {
    return objectManager.AddSceneObject(name, sceneObject);
}

TScene::ObjectHandle
TScene::AddSceneObject(const ObjectName& name, Object&& sceneObject) {
    return objectManager.AddSceneObject(name, std::move(sceneObject));
}

void TScene::RemoveSceneObject(const ObjectName& name) {
    objectManager.RemoveSceneObject(name);
}

void TScene::RemoveSceneObject(const ObjectHandle& handle) {
    objectManager.RemoveSceneObject(handle);
}

void TScene::Clear() {
    objectManager.Clear();
    componentManager.Clear();
}

bool TScene::IsEmpty() const {
    return objectManager.IsEmpty() && componentManager.IsEmpty();
}

void TScene::SetGameEngine(TGameEngine* instance) {
    componentManager.SetGameEngine(instance);
}

const TScene::ObjectManager& TScene::GetObjectManager() const {
    return objectManager;
}

TScene::ObjectManager& TScene::GetObjectManager() {
    return objectManager;
}

const TScene::ComponentManager& TScene::GetComponentManager() const {
    return componentManager;
}

TScene::ComponentManager& TScene::GetComponentManager() {
    return componentManager;
}

const TScene::ResourceManager& TScene::GetResourceManager() const {
    return resourceManager;
}

TScene::ResourceManager& TScene::GetResourceManager() {
    return resourceManager;
}

} //namespace GE
