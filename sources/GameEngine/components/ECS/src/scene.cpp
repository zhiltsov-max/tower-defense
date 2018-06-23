#include "GameEngine/ECS/scene.h"
#include "GameEngine/ECS/game_engine.h"


GE_BEGIN_ENGINE_NAMESPACE

TScene::TScene() :
    componentManager(),
    objectManager(),
    resourceManager()
{
    componentManager.SetSceneObjectManager(&objectManager);
    objectManager.SetSceneComponentManager(&componentManager);
}

TScene::TScene(TScene&& other) :
    componentManager(std::move(other.componentManager)),
    objectManager(std::move(other.objectManager)),
    resourceManager(std::move(other.resourceManager))
{
    componentManager.SetSceneObjectManager(&objectManager);
    objectManager.SetSceneComponentManager(&componentManager);
}

TScene& TScene::operator = (TScene&& other) {
    if (this != &other) {
        componentManager = std::move(other.componentManager);
        objectManager = std::move(other.objectManager);
        resourceManager = std::move(other.resourceManager);

        componentManager.SetSceneObjectManager(&objectManager);
        objectManager.SetSceneComponentManager(&componentManager);
    }
    return *this;
}

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

TScene::ObjectHandle TScene::AddSceneObject(const ObjectName& name) {
    return objectManager.CreateSceneObject(name).first;
}

TScene::ObjectHandle
TScene::AddSceneObject(const ObjectName& name, Object&& sceneObject) {
    return objectManager.CreateSceneObject(name, std::move(sceneObject)).first;
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
    resourceManager.Clear();
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

GE_END_ENGINE_NAMESPACE
