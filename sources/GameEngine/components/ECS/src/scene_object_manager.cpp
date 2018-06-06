#include "GameEngine/ECS/scene_object_manager.h"
#include "GameEngine/ECS/scene_component_manager.h"


namespace GE {

const TSceneObjectManager::ObjectHandle
TSceneObjectManager::ObjectHandle::Undefined =
    TSceneObjectManager::ObjectsAllocator::HandleUndefined;

TSceneObjectManager::TSceneObjectManager() :
    nameMapping(),
    objectsAllocator(),
    componentManager(nullptr),
    sceneObjectMessageObserver(this)
{}

TSceneObjectManager::TSceneObjectManager(TSceneObjectManager&& other) :
    nameMapping(std::move(other.nameMapping)),
    objectsAllocator(std::move(other.objectsAllocator)),
    componentManager(std::move(other.componentManager)),
    sceneObjectMessageObserver(std::move(other.sceneObjectMessageObserver))
{
    sceneObjectMessageObserver.SetOwner(this);
}

TSceneObjectManager& TSceneObjectManager::operator = (
    TSceneObjectManager&& other)
{
    if (this != &other) {
        nameMapping = std::move(other.nameMapping);
        objectsAllocator = std::move(other.objectsAllocator);
        componentManager = std::move(other.componentManager);
        sceneObjectMessageObserver =
            std::move(other.sceneObjectMessageObserver);
        sceneObjectMessageObserver.SetOwner(this);
    }
    return *this;
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const SceneObjectName& name) const {
    return GetSceneObject(name);
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const SceneObjectName& name) {
    return GetSceneObject(name);
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const SceneObjectName& name) const {
    auto handle = GetHandle(name);
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const SceneObjectName& name) {
    auto handle = GetHandle(name);
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::ObjectHandle
TSceneObjectManager::GetHandle(const SceneObjectName& name) const {
    if (nameMapping.count(name) != 0) {
        return nameMapping.at(name);
    } else {
        return ObjectHandle::Undefined;
    }
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const ObjectHandle& handle) const {
    return GetSceneObject(handle);
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::operator [] (const ObjectHandle& handle) {
    return GetSceneObject(handle);
}

const TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const ObjectHandle& handle) const {
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

TSceneObjectManager::SceneObject&
TSceneObjectManager::GetSceneObject(const ObjectHandle& handle) {
    ASSERT(handle.IsNull() == false, "Attempt to get an unexisting object.")
    return objectsAllocator[handle].second;
}

std::pair<TSceneObjectManager::ObjectHandle, TSceneObjectManager::SceneObject&>
TSceneObjectManager::CreateSceneObject(const SceneObjectName& name) {
    ASSERT(name.empty() == false, "Attempt to add an unnamed object.");
    ASSERT(HasObject(name) == false, "Object with this name already exists.");

    auto holderDeleter = [this, &name] (ObjectsAllocator::Handle* handle) {
        objectsAllocator.Deallocate(*handle);
        nameMapping.erase(name);
    };
    auto handle = objectsAllocator.Allocate();
    std::unique_ptr<decltype(handle), decltype(holderDeleter)>
        handleHolder {&handle, std::move(holderDeleter)};

    auto* entry = ::new (&objectsAllocator[handle]) Entry(name, SceneObject());
    entry->second.AsObservable().SetObserver(
        [this, handle] (const TSceneObjectMessage& message) {
            sceneObjectMessageObserver.RecieveMessage(message, handle);
        }
    );
    nameMapping[name] = handle;

    handleHolder.release();
    return {ObjectHandle(handle), entry->second};
}

std::pair<TSceneObjectManager::ObjectHandle, TSceneObjectManager::SceneObject&>
TSceneObjectManager::CreateSceneObject(const SceneObjectName& name,
    TSceneObject&& object)
{
    ASSERT(name.empty() == false, "Attempt to add an unnamed object.");
    ASSERT(HasObject(name) == false, "Object with this name already exists.");

    auto holderDeleter = [this, &name] (ObjectsAllocator::Handle* handle) {
        objectsAllocator.Deallocate(*handle);
        nameMapping.erase(name);
    };
    auto handle = objectsAllocator.Allocate();
    std::unique_ptr<decltype(handle), decltype(holderDeleter)>
        handleHolder {&handle, std::move(holderDeleter)};

    object.AsObservable().SetObserver(
        [this, handle] (const TSceneObjectMessage& message) {
            sceneObjectMessageObserver.RecieveMessage(message, handle);
        }
    );
    auto* entry = ::new (&objectsAllocator[handle])
        Entry(name, std::move(object));
    nameMapping[name] = handle;

    handleHolder.release();
    return {ObjectHandle(handle), entry->second};
}

void TSceneObjectManager::RemoveSceneObject(const SceneObjectName& name) {
    RemoveSceneObject(GetHandle(name));
}

void TSceneObjectManager::RemoveSceneObject(const ObjectHandle& handle) {
    if (HasObject(handle) == false) {
        return;
    }

    auto& entry = objectsAllocator[handle];
    nameMapping.erase(entry.first);
    entry.~Entry();
    objectsAllocator.Deallocate(handle);
}

bool TSceneObjectManager::HasObject(const SceneObjectName& name) const {
    return GetHandle(name) != ObjectHandle::Undefined;
}

bool TSceneObjectManager::HasObject(const ObjectHandle& handle) const {
    return objectsAllocator.Owns(handle) == true;
}

void TSceneObjectManager::Clear() {
    objectsAllocator = std::move(ObjectsAllocator());
    nameMapping.clear();
}

bool TSceneObjectManager::IsEmpty() const {
    return nameMapping.empty();
}

void TSceneObjectManager::SetSceneComponentManager(
    TSceneComponentManager* instance)
{
    componentManager = instance;
}

TSceneObjectManager::EntriesConstRange
TSceneObjectManager::EnumerateEntries() const {
    return {nameMapping.begin(), nameMapping.end()};
}

TSceneObjectManager::EntriesRange
TSceneObjectManager::EnumerateEntries() {
    return {nameMapping.begin(), nameMapping.end()};
}


TSceneObjectManager::SceneObjectMessageObserver::SceneObjectMessageObserver(
        TSceneObjectManager* owner) :
    owner(owner)
{}

void TSceneObjectManager::SceneObjectMessageObserver::SetOwner(
    TSceneObjectManager* instance)
{
    owner = instance;
}

void TSceneObjectManager::SceneObjectMessageObserver::RecieveMessage(
    const TSceneObjectMessage& message, const ObjectHandle& source)
{
    switch (message.type) {
    case TSceneObjectMessage::Type::ComponentAdded:
        handleMessage_ComponentAdded(message.componentAdded, source);
        break;

    case TSceneObjectMessage::Type::ComponentRemoved:
        handleMessage_ComponentRemoved(message.componentRemoved, source);
        break;

    default: /*none*/;
    }
}

void TSceneObjectManager::SceneObjectMessageObserver::
        handleMessage_ComponentAdded(
    const TSceneObjectMessage::ComponentAddedMessage& message,
    const ObjectHandle& source)
{
    ASSERT(owner != nullptr, "Owner must be set")
    ASSERT(owner->componentManager != nullptr, "Component manager is expected.")

    owner->componentManager->BindComponent(message.component,
        TSceneComponentManager::ComponentPath{source, message.entry});
}

void TSceneObjectManager::SceneObjectMessageObserver::
        handleMessage_ComponentRemoved(
    const TSceneObjectMessage::ComponentRemovedMessage& message,
    const ObjectHandle& source)
{
    ASSERT(owner != nullptr, "Owner must be set")
    ASSERT(owner->componentManager != nullptr, "Component manager is expected.")

    owner->componentManager->UnbindComponent(message.component);

    UNUSED(source);
}


TSceneObjectManager::ObjectHandle::ObjectHandle(const Value& handle) :
    handle(handle)
{}

const TSceneObjectManager::ObjectHandle::Value&
TSceneObjectManager::ObjectHandle::GetValue() const {
    return handle;
}

TSceneObjectManager::ObjectHandle::operator Value() const {
    return handle;
}

bool TSceneObjectManager::ObjectHandle::operator == (
    const ObjectHandle& other) const
{
    return handle == other.handle;
}

bool TSceneObjectManager::ObjectHandle::operator != (
    const ObjectHandle& other) const
{
    return handle != other.handle;
}

bool TSceneObjectManager::ObjectHandle::IsNull() const {
    return operator==(Undefined);
}

} // namespace GE
